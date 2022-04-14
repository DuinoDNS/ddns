#if !defined(PV_DDNS_API_CALLS_h)
	#define PV_DDNS_API_CALLS_h

	#include <module/plugin/api/api.h>

    bool PV_ddns_API_handleAPICall_get_config(
        ddns__Instance *instance,
        const char *request,
        napc__Writer *response
    );

    bool PV_ddns_API_handleAPICall_get_status(
        ddns__Instance *instance,
        const char *request,
        napc__Writer *response
    );

    bool PV_ddns_API_handleAPICall_set_debug(
        ddns__Instance *instance,
        const char *request,
        napc__Writer *response
    );
#endif
