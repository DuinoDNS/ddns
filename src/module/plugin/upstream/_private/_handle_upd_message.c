#include <module/plugin/upstream/_private/_upstream.h>

void PV_ddns_Upstream_handleUDPMessage(
	ddns__Instance *instance,
	const char *buffer, napc_size buffer_size
) {
	ddns__UpstreamContext *ctx = &instance->plugin.upstream;
	napc__DNSHeader dns_header;

	if (!napc_DNS_parseHeader(&dns_header, buffer, buffer_size)) {
		return;
	}

	napc_u16 dns_request_identifier = dns_header.request_identifier;

	// look request identifier up in requests array
	ddns__UpstreamRequest *request = PV_ddns_Upstream_getPendingRequestByID(
		ctx,
		dns_request_identifier
	);

	if (!request) {
		PV_DDNS_UPSTREAM_ERROR(
			"Received an answer from upstream to a request that is not known (req=%04x)",
			dns_request_identifier
		);

		return;
	}

	PV_ddns_Upstream_handleDNSResponse(
		instance,
		request,
		buffer,
		buffer_size
	);

	request->data_initialized = false;
}
