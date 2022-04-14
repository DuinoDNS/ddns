#include <module/plugin/api/_private/_api.h>

static void _handleAPIRequest(
	ddns__Instance *instance,
	void *context,
	napc__Buffer *buffer
) {
	NAPC_IGNORE_VALUE(context);
	NAPC_ASSERT(buffer->size == 4096);
	NAPC_ASSERT(instance->plugin.api.random_iv_ready);

	// write operations should never fail
	napc__NFWriter writer = napc_NFWriter_create(buffer->data, 1024);

	napc_mzero(buffer->data, 1024);

	// skip hmac
	napc_NFWriter_moveCurrentOffsetByAmount(&writer, 32);

	// write IV
	const napc_u8 *response_iv = instance->plugin.api.random_iv;
	napc_NFWriter_writeU8Array(&writer, 16, response_iv);

	// write request id
	napc_NFWriter_writeU8Array(&writer, 16, instance->plugin.api._request.identifier);

	// write ddns_
	napc_NFWriter_writeString(&writer, "ddns_");

	napc__Writer response_writer = napc_Writer_create(
		napc_NFWriter_getCurrentAddress(&writer),
		1024 - napc_NFWriter_getCurrentOffset(&writer)
	);

	PV_ddns_API_handleAPICall(
		instance,
		instance->plugin.api._request.body,
		&response_writer
	);

	unsigned char *response = ((unsigned char *)buffer->data) + 32 + 16;
	const char *hmac_key = instance->config.general.hashed_secret;

	NAPC_IGNORE_VALUE(
		napc_aes_encrypt(response_iv, hmac_key, response, 1024 - 32 - 16)
	);

	// hmac is at the beginning of buffer
	napc_hmac_calculate(buffer->data, hmac_key, response, 1024 - 32 - 16);

	napc_UDP_send(
		instance->plugin.api.udp_socket,
		*((napc__IPv4Participant *)context),
		buffer->data,
		1024
	);
}

void PV_ddns_API_handleAPIRequest(
	ddns__Instance *instance,
	napc__IPv4Participant source
) {
	NAPC_IGNORE_VALUE(source);

	ddns_Instance_useSharedBuffer(
		instance,
		"4k-buffer",
		&source,
		_handleAPIRequest
	);
}
