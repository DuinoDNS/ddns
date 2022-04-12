#include <module/plugin/network/_private/_network.h>

void ddns_Network_onLinkDown(ddns__Instance *instance) {
	ddns__NetworkContext *ctx = &instance->plugin.network;

	napc_UDP_closeSocket(ctx->udp_out);
	ctx->is_ready = false;
}
