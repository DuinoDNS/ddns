#include <module/plugin/upstream/_private/_upstream.h>

void ddns_Upstream_loop(ddns__Instance *instance) {
	// handle any incoming udp messages
	PV_ddns_Upstream_handleUDPSocket(instance);
	// cancel old requests
	PV_ddns_Upstream_cancelAgedRequests(instance);
}
