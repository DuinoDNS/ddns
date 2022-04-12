#include <module/plugin/upstream/_private/_upstream.h>

ddns__UpstreamRequest *PV_ddns_Upstream_getNextFreeRequest(
	ddns__UpstreamContext *ctx
) {
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(ctx->requests); ++i) {
		ddns__UpstreamRequest *r = &ctx->requests[i];

		// return the first uninitialized slot
		if (!r->data_initialized) return r;
	}

	return NULL;
}
