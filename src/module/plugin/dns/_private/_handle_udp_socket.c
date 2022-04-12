#include <module/plugin/dns/_private/_dns.h>

static void _handleUDPSocket(ddns__Instance *instance, void *context, napc__Buffer *buffer) {
	NAPC_IGNORE_VALUE(context);

	ddns__DNSContext *ctx = &instance->plugin.dns;
	napc__IPv4Participant source;

	if (!napc_UDP_receive(ctx->udp_in, &source, buffer)) {
		return;
	}

	PV_DDNS_DNS_INFO(
		"Got DNS-Request from client (source=%s:%u) (size=%" NAPC_SIZE_PRINTF ")",
		source.addr, source.port, buffer->size
	);

	PV_ddns_DNS_handleUDPMessage(
		instance, source, buffer->data, buffer->size
	);
}

void PV_ddns_DNS_handleUDPSocket(
	ddns__Instance *instance
) {
	ddns_Instance_useSharedBuffer(
		instance,
		"4k-buffer-1",
		NULL,
		_handleUDPSocket
	);
}
