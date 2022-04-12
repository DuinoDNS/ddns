#include <module/plugin/upstream/_private/_upstream.h>

void PV_ddns_Upstream_cancelAgedRequests(
	ddns__Instance *instance
) {
	ddns__UpstreamContext *ctx = &instance->plugin.upstream;

	// cancel any requests that have been unanswered for
	// x amount of milliseconds
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(ctx->requests); ++i) {
		ddns__UpstreamRequest *r = &ctx->requests[i];

		// Ignore non-initialized requests
		if (!r->data_initialized) continue;

		napc_time delta = napc_getTimeSinceBoot() - r->requested_at;

		if (delta >= instance->config.upstream.timeout) {
			PV_DDNS_UPSTREAM_INFO(
				"Cancelling upstream request because it timed out. (req=%04x)",
				r->dns_request_identifier
			);

			r->data_initialized = false;

			// Statistics //
			ddns_Statistics_setDNSRequestTimeout(instance, r->dns_request_identifier);
			// Statistics //
		}
	}
}
