#if !defined(PV_DDNS_API_CALLS_h)
	#define PV_DDNS_API_CALLS_h

	#include <module/_private/_ddns.h>

    bool PV_ddns_handleAPICall_clear_debug(
        ddns__Instance *instance,
        const char *request,
        napc__Writer *response
    );

    bool PV_ddns_handleAPICall_get_config_section(
        ddns__Instance *instance,
        const char *request,
        napc__Writer *response
    );

    bool PV_ddns_handleAPICall_get_queries(
        ddns__Instance *instance,
        const char *request,
        napc__Writer *response
    );

    bool PV_ddns_handleAPICall_get_status(
        ddns__Instance *instance,
        const char *request,
        napc__Writer *response
    );

    bool PV_ddns_handleAPICall_restart(
        ddns__Instance *instance,
        const char *request,
        napc__Writer *response
    );

    bool PV_ddns_handleAPICall_set_debug(
        ddns__Instance *instance,
        const char *request,
        napc__Writer *response
    );
#endif
