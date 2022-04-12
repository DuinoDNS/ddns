#include <module/plugin/upstream/_private/_upstream.h>

void ddns_Upstream_onLinkUp(ddns__Instance *instance) {
	ddns__UpstreamContext *ctx = &instance->plugin.upstream;

	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(ctx->requests); ++i) {
		ctx->requests[i].data_initialized = false;
	}

	ctx->upstream_address = napc_IPv4Participant_create(
		instance->config.upstream.address,
		instance->config.upstream.port
	);
}
