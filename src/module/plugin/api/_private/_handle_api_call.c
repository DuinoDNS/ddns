/*
 * NOTICE: This file was automatically generated.
 */
#include <module/plugin/api/_private/_api.h>

bool PV_ddns_API_handleAPICall(
    ddns__Instance *instance,
    const char *request,
    napc__Writer *response
) {

    if (napc_memeql(request, "get_config", napc_strlen("get_config"))) {
        const char *body = request + napc_strlen("get_config");

        PV_DDNS_API_DEBUG("Handling API Call 'get_config'");
        return PV_ddns_API_handleAPICall_get_config(instance, body, response);
    }

    if (napc_memeql(request, "get_status", napc_strlen("get_status"))) {
        const char *body = request + napc_strlen("get_status");

        PV_DDNS_API_DEBUG("Handling API Call 'get_status'");
        return PV_ddns_API_handleAPICall_get_status(instance, body, response);
    }

    if (napc_memeql(request, "set_debug", napc_strlen("set_debug"))) {
        const char *body = request + napc_strlen("set_debug");

        PV_DDNS_API_DEBUG("Handling API Call 'set_debug'");
        return PV_ddns_API_handleAPICall_set_debug(instance, body, response);
    }

    PV_DDNS_API_SECURITY("Unknown API call.");

    return false;
}
