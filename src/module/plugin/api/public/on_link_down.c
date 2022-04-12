#include <module/plugin/api/_private/_api.h>

void ddns_API_onLinkDown(ddns__Instance *instance) {
	ddns__APIContext *ctx = &instance->plugin.api;

	napc_UDP_closeSocket(ctx->udp_socket);
}
