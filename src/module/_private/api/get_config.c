#include <module/_private/_ddns.h>

bool PV_ddns_handleAPICall_get_config(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	if (!ddns_Config_write(
		&instance->config,
		"general",
		response
	)) {
		return false;
	}

	if (!napc_Writer_writeChar(response, 0)) {
		return false;
	}

	return true;
}
