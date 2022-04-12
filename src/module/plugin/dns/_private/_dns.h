#if !defined(PV_DDNS_DNS_h)
	#define PV_DDNS_DNS_h

	#include <module/plugin/dns/dns.h>
	#include <module/plugin/dns/_private/_log.h>

	#include <module/instance/instance.h>

	void PV_ddns_DNS_handleUDPSocket(
		ddns__Instance *instance
	);

	void PV_ddns_DNS_handleUDPMessage(
		ddns__Instance *instance,
		napc__IPv4Participant client,
		const char *buffer, napc_size buffer_size
	);

	void PV_ddns_DNS_handleDNSRequest(
		ddns__Instance *instance,
		napc__IPv4Participant client,
		napc__DNSRequest *dns_request,
		const char *buffer, napc_size buffer_size
	);
#endif
