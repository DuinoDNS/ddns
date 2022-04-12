#include <module/plugin/upstream/_private/_upstream.h>

ddns__UpstreamRequest *PV_ddns_Upstream_getPendingRequestByID(
	ddns__UpstreamContext *ctx,
	napc_u16 dns_request_identifier
) {
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(ctx->requests); ++i) {
		ddns__UpstreamRequest *r = &ctx->requests[i];

		// ignore non-initialized requests
		if (!r->data_initialized) continue;

		if (r->dns_request_identifier == dns_request_identifier) {
			return r;
		}
	}

	return NULL;
}
