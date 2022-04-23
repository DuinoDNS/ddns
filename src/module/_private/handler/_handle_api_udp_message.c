#include <module/_private/_ddns.h>

static napc_u8 _request_hmac[32]; // @static
static napc_u8 _request_iv[16]; // @static

/*
 * This function gets called whenever a message appears
 * on the UDP socket that is listening on the api.listen_port port.
 */
void PV_ddns_handleAPIUDPMessage(
	ddns__Instance *instance, napc__IPv4Participant *client, napc__Buffer buffer
) {
	// hmac + iv + payload = 1024 bytes
	// only use 1024 bytes (MTU limit)
	if (buffer.size != 1024) {
		PV_DDNS_ERROR("Unexpected packet size %" NAPC_SIZE_PRINTF, buffer.size);

		return;
	}

	PV_DDNS_DEBUG(
		"Received API request from client (size=%" NAPC_SIZE_PRINTF ")",
		buffer.size
	);

	// cast to unsigned char to perform pointer arithmetic
	unsigned char *request = buffer.data;

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
		PV_DDNS_SECURITY("Invalid HMAC signature.");

		napc_UDP_send(
			instance->api_udp_in,
			*client,
			"ddns_invalid_hmac",
			napc_strlen("ddns_invalid_hmac")
		);

		return;
	}

	// decrypt payload
	if (!napc_aes_decrypt(_request_iv, hmac_key, ciphertext, 1024 - 32 - 16)) {
		PV_DDNS_ERROR("Failed to decrypt request.");

		return;
	}

	// check for ddns_
	if (!napc_memeql(ciphertext, "ddns_", 5)) {
		PV_DDNS_ERROR("ddns_ prefix is missing from payload.");

		return;
	}

	// read request identifier
	for (napc_size i = 0; i < 16; ++i) {
		instance->api.request_identifier[i] = ciphertext[5 + i];
	}

	char *payload = (char *)(ciphertext + 5 + 16);

	// make sure payload is always NUL-terminated
	payload[1023] = 0;

	instance->api.body = payload;

	PV_ddns_handleAPIRequest(instance, client);
}
