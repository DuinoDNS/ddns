#include <module/plugin/upstream/_private/_upstream.h>

void ddns_Upstream_sendRequest(
	ddns__Instance *instance,
	napc__IPv4Participant requester,
	const char *buffer, napc_size buffer_size
) {
	ddns__UpstreamContext *ctx = &instance->plugin.upstream;

	if (!instance->config.upstream.enabled) {
		PV_DDNS_UPSTREAM_INFO("Upstream has been disabled.");

		return;
	}

	napc__DNSHeader dns_header;

	if (!napc_DNS_parseHeader(&dns_header, buffer, buffer_size)) {
		PV_DDNS_UPSTREAM_ERROR("Failed to parse DNS-Header.");

		return;
	}

	ddns__UpstreamRequest *slot = PV_ddns_Upstream_getNextFreeRequest(ctx);

	if (!slot) {
		PV_DDNS_UPSTREAM_ERROR(
			"Cannot send request to upstream because all request slots are busy!"
		);

		return;
	}

	slot->data_initialized = true;
	slot->requested_at = napc_getTimeSinceBoot(); // used for request timeout
	slot->dns_request_identifier = dns_header.request_identifier;
	slot->requester = requester;

	// send request to upstream server
	ddns_Network_send(
		instance,
		ctx->upstream_address,
		buffer,
		buffer_size
	);
}
