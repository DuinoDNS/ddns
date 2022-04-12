#if !defined(DDNS_NETWORK_h)
	#define DDNS_NETWORK_h

	#include <napc.h>

	// Type forwarding to avoid including "instance.h"
	// because instance.h includes this file
	typedef struct ddns__Instance ddns__Instance;

	typedef struct {
		bool            is_ready;
		napc__UDPSocket udp_out;
	} ddns__NetworkContext;

	// only called ONCE in the program's lifecycle
	void ddns_Network_onBoot(ddns__Instance *instance);
	// called when ethernet link goes from DOWN->UP
	void ddns_Network_onLinkUp(ddns__Instance *instance);
	// called when ethernet link goes from UP->DOWN
	void ddns_Network_onLinkDown(ddns__Instance *instance);
	// continuously called when ethernet link is up
	void ddns_Network_loop(ddns__Instance *instance);


	void ddns_Network_send(
		ddns__Instance *instance,
		napc__IPv4Participant destination,
		const char *buffer, napc_size buffer_size
	);

	bool ddns_Network_receive(
		ddns__Instance *instance,
		napc__IPv4Participant *source,
		napc__Buffer *buffer
	);

#endif
