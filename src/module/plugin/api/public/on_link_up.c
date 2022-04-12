#include <module/plugin/api/_private/_api.h>

void ddns_API_onLinkUp(ddns__Instance *instance) {
	ddns__APIContext *ctx = &instance->plugin.api;

	ctx->udp_socket = napc_UDP_createSocket(
		instance->config.api.listen_port
	);
	ctx->random_iv_ready = false;
}
