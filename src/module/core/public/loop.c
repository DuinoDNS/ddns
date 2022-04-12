#include <module/core/_private/_core.h>

void ddns_loop(ddns__Instance *instance) {
	bool eth_link_status = napc_eth_getLinkStatus();

	if (eth_link_status && !instance->eth_link_status) {
		PV_DDNS_INFO("Ethernet Link status changed from DOWN to UP.");

		ddns_Network_onLinkUp(instance);
		ddns_Statistics_onLinkUp(instance);
		ddns_DNS_onLinkUp(instance);
		ddns_Upstream_onLinkUp(instance);
		ddns_API_onLinkUp(instance);
	} else if (!eth_link_status && instance->eth_link_status) {
		PV_DDNS_INFO("Ethernet Link status changed from UP to DOWN.");

		ddns_Network_onLinkDown(instance);
		ddns_Statistics_onLinkDown(instance);
		ddns_DNS_onLinkDown(instance);
		ddns_Upstream_onLinkDown(instance);
		ddns_API_onLinkDown(instance);
	}

	if (eth_link_status) {
		ddns_Network_loop(instance);
		ddns_Statistics_loop(instance);
		ddns_DNS_loop(instance);
		ddns_Upstream_loop(instance);
		ddns_API_loop(instance);
	}

	instance->eth_link_status = eth_link_status;
}
