#include <module/plugin/dns/_private/_dns.h>

void ddns_DNS_loop(ddns__Instance *instance) {
	PV_ddns_DNS_handleUDPSocket(instance);
}
