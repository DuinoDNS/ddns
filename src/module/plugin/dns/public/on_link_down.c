#include <module/plugin/dns/_private/_dns.h>

void ddns_DNS_onLinkDown(ddns__Instance *instance) {
	ddns__DNSContext *ctx = &instance->plugin.dns;

	napc_UDP_closeSocket(ctx->udp_in);
}
