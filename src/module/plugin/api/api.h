#if !defined(DDNS_API_h)
	#define DDNS_API_h

	#include <napc.h>

	// Type forwarding to avoid including "instance.h"
	// because instance.h includes this file
	typedef struct ddns__Instance ddns__Instance;

	typedef struct {
		napc__UDPSocket     udp_socket;
		napc_u8             random_iv[16];
		bool                random_iv_ready;

		struct {
			napc_u8 identifier[16];
			const char *body;
		} _request;
	} ddns__APIContext;

	// only called ONCE in the program's lifecycle
	void ddns_API_onBoot(ddns__Instance *instance);
	// called when ethernet link goes from DOWN->UP
	void ddns_API_onLinkUp(ddns__Instance *instance);
	// called when ethernet link goes from UP->DOWN
	void ddns_API_onLinkDown(ddns__Instance *instance);
	// continuously called when ethernet link is up
	void ddns_API_loop(ddns__Instance *instnace);
#endif
