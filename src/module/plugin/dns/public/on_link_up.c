#include <module/plugin/dns/_private/_dns.h>

void ddns_DNS_onLinkUp(ddns__Instance *instance) {
	ddns__DNSContext *ctx = &instance->plugin.dns;

	ctx->udp_in = napc_UDP_createSocket(
		instance->config.dns.listen_port
	);
}
