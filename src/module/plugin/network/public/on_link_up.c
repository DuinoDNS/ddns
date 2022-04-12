#include <module/plugin/network/_private/_network.h>

void ddns_Network_onLinkUp(ddns__Instance *instance) {
	ddns__NetworkContext *ctx = &instance->plugin.network;

	napc_eth_setMACAddress(instance->config.network.mac_address);
	napc_eth_setIPAddress(instance->config.network.address);
	napc_eth_setSubnetMask(instance->config.network.netmask);
	napc_eth_setGatewayAddress(instance->config.network.gateway);

	ctx->udp_out = napc_UDP_createSocket(
		instance->config.network.out_port
	);

	ctx->is_ready = true;
}
