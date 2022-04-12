#if !defined(DDNS_DNS_h)
	#define DDNS_DNS_h

	#include <napc.h>

	// Type forwarding to avoid including "instance.h"
	// because instance.h includes this file
	typedef struct ddns__Instance ddns__Instance;

	typedef struct {
		//duinodns_dns__Record records[32];
		napc__UDPSocket  udp_in;
	} ddns__DNSContext;

	// only called ONCE in the program's lifecycle
	void ddns_DNS_onBoot(ddns__Instance *instance);
	// called when ethernet link goes from DOWN->UP
	void ddns_DNS_onLinkUp(ddns__Instance *instance);
	// called when ethernet link goes from UP->DOWN
	void ddns_DNS_onLinkDown(ddns__Instance *instance);
	// continuously called when ethernet link is up
	void ddns_DNS_loop(ddns__Instance *instance);
#endif
