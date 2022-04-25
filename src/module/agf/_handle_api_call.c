/*
 * NOTICE: This file was automatically generated.
 */
#include <module/_private/_ddns.h>
#include <module/agf/_api_calls.h>

bool PV_AGF_ddns_handleAPICall(
    ddns__Instance *instance,
    const char *request,
    napc__Writer *response
) {

    if (napc_memeql(request, "get_config", napc_strlen("get_config"))) {
        const char *body = request + napc_strlen("get_config");

        PV_DDNS_DEBUG("Handling API Call 'get_config'");
        return PV_ddns_handleAPICall_get_config(instance, body, response);
    }

    PV_DDNS_SECURITY("Unknown API call.");

    return false;
}
