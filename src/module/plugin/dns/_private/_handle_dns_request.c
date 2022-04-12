#include <module/plugin/dns/_private/_dns.h>

void PV_ddns_DNS_handleDNSRequest(
	ddns__Instance *instance,
	napc__IPv4Participant client,
	napc__DNSRequest *dns_request,
	const char *buffer, napc_size buffer_size
) {
	NAPC_IGNORE_VALUE(dns_request);
	//if (_localResolve(instance, client, dns_query)) {
	//	return;
	//}

	PV_DDNS_DNS_DEBUG(
		"Cannot resolve name locally, trying to send to upstream (%s:%" NAPC_U16_PRINTF ")...",
		instance->config.upstream.address,
		instance->config.upstream.port
	);

	ddns_Upstream_sendRequest(instance, client, buffer, buffer_size);
}
