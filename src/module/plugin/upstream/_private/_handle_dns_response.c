#include <module/plugin/upstream/_private/_upstream.h>

void PV_ddns_Upstream_handleDNSResponse(
	ddns__Instance *instance,
	ddns__UpstreamRequest *request,
	const char *buffer, napc_size buffer_size
) {
	napc__DNSResponse dns_response;

	if (napc_DNS_parseResponse(&dns_response, buffer, buffer_size)) {
		// Statistics //
			ddns_Statistics_setDNSRequestResolved(
				instance,
				&dns_response,
				false
			);
		// Statistics //

		switch (dns_response.header.response_code) {
			case 1: {
				PV_DDNS_UPSTREAM_ERROR(
					"Upstream responded with: unable to interpret the query."
				);
			} break;

			case 2: {
				PV_DDNS_UPSTREAM_ERROR(
					"Upstream responded with: unable to process this query."
				);
			} break;

			case 5: {
				PV_DDNS_UPSTREAM_ERROR(
					"Upstream responded with: refuse to fulfill this query."
				);
			} break;
		}
	} else {
		// Statistics //
		/*
		duinodns_stats__setQueryResolved(
			instance,
			request->dns_request_identifier,
			false,
			0x00,
			NULL,
			false
		);*/
		// Statistics //
	}

	// Relay upstream response to client
	napc_UDP_send(
		instance->plugin.dns.udp_in,
		request->requester,
		buffer, buffer_size
	);
}
