#include <module/plugin/network/_private/_network.h>

bool ddns_Network_receive(
	ddns__Instance *instance,
	napc__IPv4Participant *source,
	napc__Buffer *buffer
) {
	ddns__NetworkContext *ctx = &instance->plugin.network;

	if (!ctx->is_ready) return false;

	return napc_UDP_receive(
		ctx->udp_out,
		source,
		buffer
	);
}
