#include <module/plugin/dns/_private/_dns.h>

void PV_ddns_DNS_handleUDPMessage(
	ddns__Instance *instance,
	napc__IPv4Participant client,
	const char *buffer, napc_size buffer_size
) {
	napc__DNSRequest dns_request;

	if (!napc_DNS_parseRequest(&dns_request, buffer, buffer_size)) {
		PV_DDNS_DNS_ERROR("Failed to parse DNS-Request.");

		// still handle query, relay it to the upstream
		PV_ddns_DNS_handleDNSRequest(
			instance, client, NULL, buffer, buffer_size
		);

		return;
	}

	PV_DDNS_DNS_INFO(
		"Parsed DNS-Request for '%s' (type=%4.4x,req=%04x)",
		dns_request.query.name, dns_request.query.qtype, dns_request.header.request_identifier
	);

	// Statistics //
	napc_u8 client_ip[4];

	if (napc_parser_parseIPv4Address(client.addr, client_ip)) {
		ddns_Statistics_registerDNSRequest(
			instance, &dns_request, client_ip
		);
	}
	// Statistics //

	PV_ddns_DNS_handleDNSRequest(
		instance,
		client,
		&dns_request,
		buffer, buffer_size
	);
}
