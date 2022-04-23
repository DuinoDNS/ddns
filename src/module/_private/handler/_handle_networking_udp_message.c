#include <module/_private/_ddns.h>

/*
 * This function gets called whenever a message appears from the
 * upstream DNS server.
 */
void PV_ddns_handleNetworkingUDPMessage(
	ddns__Instance *instance, napc__IPv4Participant *client, napc__Buffer buffer
) {
	/*
	 * Attempt to parse DNS header because we need dns_header.request_identifier
	 */
	napc__DNSHeader dns_header;

	if (!napc_DNS_parseHeader(&dns_header, buffer.data, buffer.size)) {
		PV_DDNS_ERROR("Could not parse DNS-header. Nothing more to do.");

		return;
	}

	PV_DDNS_DEBUG(
		"Parsed DNS-Query header: request identifier is 0x%04x", dns_header.request_identifier
	);

	ddns__Query *q = PV_ddns_getQueryByRequestIdentifier(
		instance,
		dns_header.request_identifier
	);

	if (!q) {
		PV_DDNS_ERROR(
			"No query in list that is associated with"
			" the request identifier 0x%04x",
			dns_header.request_identifier
		);

		return;
	}

	NAPC_ASSERT(q->meta_initialized);

	q->has_response = napc_DNS_parseResponse(&q->response, buffer.data, buffer.size);

	napc_UDP_send(
		instance->dns_udp_in, q->meta.requester, buffer.data, buffer.size
	);

	q->meta.state = DDNS_QUERY_STATE_COMPLETED;
}
