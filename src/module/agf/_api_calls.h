#if !defined(PV_DDNS_API_CALLS_h)
	#define PV_DDNS_API_CALLS_h

	#include <module/_private/_ddns.h>

    bool PV_ddns_handleAPICall_get_config(
        ddns__Instance *instance,
        const char *request,
        napc__Writer *response
    );
#endif
