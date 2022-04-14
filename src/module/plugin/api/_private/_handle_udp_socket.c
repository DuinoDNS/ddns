#include <module/plugin/api/_private/_api.h>

static napc_u8 _request_hmac[32]; // @global
static napc_u8 _request_iv[16]; // @global

static void _handleUDPSocket(
	ddns__Instance *instance,
	void *context,
	napc__Buffer *buffer
) {
	NAPC_IGNORE_VALUE(context);

	ddns__APIContext *ctx = &instance->plugin.api;
	napc__IPv4Participant source;

	if (!napc_UDP_receive(ctx->udp_socket, &source, buffer)) {
		return;
	}

	// hmac + iv + payload = 1024 bytes
	// only use 1024 bytes (MTU limit)
	if (buffer->size != 1024) {
		PV_DDNS_API_ERROR("Unexpected packet size %" NAPC_SIZE_PRINTF, buffer->size);

		return;
	}

	PV_DDNS_API_DEBUG(
		"Received API request from client (size=%" NAPC_SIZE_PRINTF ")",
		buffer->size
	);

	// cast to unsigned char to perform pointer arithmetic
	unsigned char *request = buffer->data;

	// read request hmac
	for (napc_size i = 0; i < 32; ++i) {
		_request_hmac[i] = request[i];
	}

	// read request iv
	for (napc_size i = 0; i < 16; ++i) {
		_request_iv[i] = request[32 + i];
	}

	unsigned char *ciphertext = request + 32 + 16;
	const char *hmac_key = instance->config.general.hashed_secret;

	// check hmac signature
	if (!napc_hmac_verify(hmac_key, _request_hmac, ciphertext, 1024 - 32 - 16)) {
		PV_DDNS_API_SECURITY("Invalid HMAC signature.");

		napc_UDP_send(
			instance->plugin.api.udp_socket,
			source,
			"ddns_invalid_hmac",
			napc_strlen("ddns_invalid_hmac")
		);

		return;
	}

	// decrypt payload
	if (!napc_aes_decrypt(_request_iv, hmac_key, ciphertext, 1024 - 32 - 16)) {
		PV_DDNS_API_ERROR("Failed to decrypt request.");

		return;
	}

	// check for ddns_
	if (!napc_memeql(ciphertext, "ddns_", 5)) {
		PV_DDNS_API_ERROR("ddns_ prefix is missing from payload.");

		return;
	}

	// read request identifier
	for (napc_size i = 0; i < 16; ++i) {
		ctx->_request.identifier[i] = ciphertext[5 + i];
	}

	char *payload = (char *)(ciphertext + 5 + 16);

	// make sure payload is always NUL-terminated
	payload[1023] = 0;

	ctx->_request.body = payload;

	PV_ddns_API_handleAPIRequest(instance, source);
}

void PV_ddns_API_handleUDPSocket(
	ddns__Instance *instance
) {
	ddns_Instance_useSharedBuffer(
		instance,
		"1k-buffer",
		NULL,
		_handleUDPSocket
	);
}
