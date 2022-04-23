#include <module/_private/_ddns.h>

void ddns_loop(ddns__Instance *instance) {
	bool eth_link_status = napc_eth_getLinkStatus();

	if (eth_link_status && !instance->eth_link_status) {
		PV_DDNS_INFO("Ethernet Link status changed from DOWN to UP.");

		PV_ddns_onLinkUp(instance);
	} else if (!eth_link_status && instance->eth_link_status) {
		PV_DDNS_INFO("Ethernet Link status changed from UP to DOWN.");

		PV_ddns_onLinkDown(instance);
	}

	if (eth_link_status) {
		PV_ddns_runLoop(instance);
	}

	instance->eth_link_status = eth_link_status;
}
