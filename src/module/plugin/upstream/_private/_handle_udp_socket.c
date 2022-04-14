#include <module/plugin/upstream/_private/_upstream.h>

static void _handleUDPSocket(
	ddns__Instance *instance,
	void *context,
	napc__Buffer *buffer
) {
	NAPC_IGNORE_VALUE(context);

	napc__IPv4Participant source;

	if (!ddns_Network_receive(instance, &source, buffer)) {
		return;
	}

	PV_DDNS_UPSTREAM_DEBUG(
		"Received message on upstream UDP-port (%s:%u)",
		source.addr, source.port
	);

	// check if source is really upstream
	if (!napc_streql(source.addr, instance->config.upstream.address)) {
		PV_DDNS_UPSTREAM_SECURITY(
			"Message is not from configured upstream IP address!"
		);

		return;
	}

	PV_ddns_Upstream_handleUDPMessage(
		instance, buffer->data, buffer->size
	);
}

void PV_ddns_Upstream_handleUDPSocket(
	ddns__Instance *instance
) {
	ddns_Instance_useSharedBuffer(
		instance,
		"1k-buffer",
		NULL,
		_handleUDPSocket
	);
}
