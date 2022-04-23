#include <module/_private/_ddns.h>

void PV_ddns_onLinkUp(ddns__Instance *instance) {
	instance->dns_udp_in = napc_UDP_createSocket(instance->config.dns.listen_port);
	instance->networking_udp_out = napc_UDP_createSocket(instance->config.network.out_port);
	instance->api_udp_in = napc_UDP_createSocket(instance->config.api.listen_port);

	// init queries
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(instance->queries); ++i) {
		ddns__Query *q = &instance->queries[i];

		q->meta_initialized = false;
	}

	instance->api.random_iv_ready = false;
}
