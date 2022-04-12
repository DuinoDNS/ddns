#include <module/plugin/api/_private/_api.h>

void ddns_API_loop(ddns__Instance *instance) {
	ddns__APIContext *ctx = &instance->plugin.api;

	if (!ctx->random_iv_ready) {
		if (napc_random_getRandomBytes(sizeof(ctx->random_iv), ctx->random_iv)) {
			ctx->random_iv_ready = true;

			PV_DDNS_API_INFO("Random IV is ready.");
		}
	}

	if (ctx->random_iv_ready) {
		PV_ddns_API_handleUDPSocket(instance);
	}
}
