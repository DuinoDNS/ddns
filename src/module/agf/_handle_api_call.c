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

    if (napc_memeql(request, "clear_debug", napc_strlen("clear_debug"))) {
        const char *body = request + napc_strlen("clear_debug");

        PV_DDNS_DEBUG("Handling API Call 'clear_debug'");
        return PV_ddns_handleAPICall_clear_debug(instance, body, response);
    }

    if (napc_memeql(request, "get_config", napc_strlen("get_config"))) {
        const char *body = request + napc_strlen("get_config");

        PV_DDNS_DEBUG("Handling API Call 'get_config'");
        return PV_ddns_handleAPICall_get_config(instance, body, response);
    }

    if (napc_memeql(request, "get_queries", napc_strlen("get_queries"))) {
        const char *body = request + napc_strlen("get_queries");

        PV_DDNS_DEBUG("Handling API Call 'get_queries'");
        return PV_ddns_handleAPICall_get_queries(instance, body, response);
    }

    if (napc_memeql(request, "set_debug", napc_strlen("set_debug"))) {
        const char *body = request + napc_strlen("set_debug");

        PV_DDNS_DEBUG("Handling API Call 'set_debug'");
        return PV_ddns_handleAPICall_set_debug(instance, body, response);
    }

    PV_DDNS_SECURITY("Unknown API call.");

    return false;
}
