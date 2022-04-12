#if !defined(PV_DDNS_UPSTREAM_h)
	#define PV_DDNS_UPSTREAM_h

	#include <module/plugin/upstream/upstream.h>
	#include <module/plugin/upstream/_private/_log.h>

	#include <module/instance/instance.h>
	#include <module/plugin/network/network.h>

	void PV_ddns_Upstream_handleUDPSocket(
		ddns__Instance *instance
	);

	void PV_ddns_Upstream_handleUDPMessage(
		ddns__Instance *instance,
		const char *buffer, napc_size buffer_size
	);

	/*
	 * Gets the a request identified by dns_request_identifier.
	 */
	ddns__UpstreamRequest *PV_ddns_Upstream_getPendingRequestByID(
		ddns__UpstreamContext *ctx,
		napc_u16 dns_request_identifier
	);

	/*
	 * Gets the next free request slot.
	 * Returns NULL if no free slot is available at the time.
	 */
	ddns__UpstreamRequest *PV_ddns_Upstream_getNextFreeRequest(
		ddns__UpstreamContext *ctx
	);

	/*
	 * Invalidates pending requests after set timeout.
	 */
	void PV_ddns_Upstream_cancelAgedRequests(
		ddns__Instance *instance
	);

	void PV_ddns_Upstream_handleDNSResponse(
		ddns__Instance *instance,
		ddns__UpstreamRequest *request,
		const char *buffer, napc_size buffer_size
	);
#endif
