#include <module/_private/_ddns.h>

static void _handleUDPSocket(
	ddns__Instance *instance, void *context, napc__Buffer *buffer
) {
	const char *what = context;

	napc__UDPSocket udp_socket;
	void (*handler)(ddns__Instance *, napc__IPv4Participant *, napc__Buffer) = NULL;

	if (napc_streqli(what, "dns")) {
		udp_socket = instance->dns_udp_in;
		handler = PV_ddns_handleDNSUDPMessage;
	} else if (napc_streqli(what, "networking")) {
		udp_socket = instance->networking_udp_out;
		handler = PV_ddns_handleNetworkingUDPMessage;
	} else if (napc_streqli(what, "api")) {
		udp_socket = instance->api_udp_in;
		handler = PV_ddns_handleAPIUDPMessage;
	}

	if (!handler) return;

	napc__IPv4Participant client;

	if (!napc_UDP_receive(udp_socket, &client, buffer)) {
		return;
	}

	PV_DDNS_DEBUG(
		"Received %" NAPC_SIZE_PRINTF " bytes from client %s"
		" (udp_socket=%s)",
		buffer->size, client.addr, what
	);

	if (handler) {
		handler(
			instance, &client, *buffer
		);
	}
}

void PV_ddns_runLoop(ddns__Instance *instance) {
	PV_ddns_useSharedBuffer(instance, "1k-buffer", (void *)"dns", _handleUDPSocket);
	PV_ddns_useSharedBuffer(instance, "1k-buffer", (void *)"networking", _handleUDPSocket);

	if (napc_random_getRandomBytes(sizeof(instance->api.random_iv), instance->api.random_iv)) {
		instance->api.random_iv_ready = true;
	}

	if (instance->api.random_iv_ready) {
		PV_ddns_useSharedBuffer(instance, "1k-buffer", (void *)"api", _handleUDPSocket);
	}

	/**
	 * Mark queries that are too old.
	 */
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(instance->queries); ++i) {
		ddns__Query *q = &instance->queries[i];

		if (!q->meta_initialized) continue;
		if (q->meta.state != DDNS_QUERY_STATE_INITIALIZED) continue;

		napc_time delta = napc_getTimeSinceBoot() - q->meta.received_at;

		if (delta >= instance->config.upstream.timeout) {
			q->meta.state = DDNS_QUERY_STATE_TIMEOUT;
		}
	}

	napc_random_collectBytes();


	if (napc_Timer_expired(&instance->tmr)) {
		napc_Timer_restart(&instance->tmr);

		napc_printf("\n\n");

		for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(instance->queries); ++i) {
			ddns__Query *q = &instance->queries[i];

			napc_printf(
				"%3ld. %s %04x state %d",
				i+1,
				q->meta_initialized ? "meta initialized" : "                ",
				q->meta_initialized ? q->meta.dns_header.request_identifier : 0,
				q->meta_initialized ? q->meta.state : -1
			);

			if (q->meta_initialized && q->meta.state == DDNS_QUERY_STATE_INITIALIZED) {
				napc_printf(" INITIALIZED ");
			} else if (q->meta_initialized && q->meta.state == DDNS_QUERY_STATE_TIMEOUT) {
				napc_printf(" TIMEOUT ");

			} else if (q->meta_initialized && q->meta.state == DDNS_QUERY_STATE_COMPLETED) {
				napc_printf(" COMPLETED ");
			}

			if (q->meta_initialized) {
				if (q->has_request) {
					napc_printf(" HAS_REQUEST=yes ");
				}
				if (q->has_response) {
					napc_printf(" HAS_RESPONSE=yes ");
				}
			}

			napc_printf("\n");
		}
	}
}
