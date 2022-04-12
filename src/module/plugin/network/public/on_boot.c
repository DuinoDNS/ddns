#include <module/plugin/network/_private/_network.h>

void ddns_Network_onBoot(ddns__Instance *instance) {
	ddns__NetworkContext *ctx = &instance->plugin.network;

	ctx->is_ready = false;
}
