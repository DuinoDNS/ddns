#include <module/plugin/network/_private/_network.h>

void ddns_Network_send(
	ddns__Instance *instance,
	napc__IPv4Participant destination,
	const char *buffer,napc_size buffer_size
) {
	ddns__NetworkContext *ctx = &instance->plugin.network;

	if (!ctx->is_ready) return;

	napc_UDP_send(
		ctx->udp_out,
		destination,
		buffer, buffer_size
	);
}
