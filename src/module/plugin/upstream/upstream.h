#if !defined(DDNS_UPSTREAM_h)
	#define DDNS_UPSTREAM_h

	#include <napc.h>

	// Type forwarding to avoid including "instance.h"
	// because instance.h includes this file
	typedef struct ddns__Instance ddns__Instance;

	typedef struct {
		bool data_initialized;
		napc_u16 dns_request_identifier;
		napc__IPv4Participant requester;
		napc_time requested_at;
	} ddns__UpstreamRequest;

	typedef struct {
		ddns__UpstreamRequest requests[8];
		napc__IPv4Participant upstream_address;
	} ddns__UpstreamContext;

	// only called ONCE in the program's lifecycle
	void ddns_Upstream_onBoot(ddns__Instance *instance);
	// called when ethernet link goes from DOWN->UP
	void ddns_Upstream_onLinkUp(ddns__Instance *instance);
	// called when ethernet link goes from UP->DOWN
	void ddns_Upstream_onLinkDown(ddns__Instance *instance);
	// continuously called when ethernet link is up
	void ddns_Upstream_loop(ddns__Instance *instance);


	void ddns_Upstream_sendRequest(
		ddns__Instance *instance,
		napc__IPv4Participant requester,
		const char *buffer, napc_size buffer_size
	);
#endif
