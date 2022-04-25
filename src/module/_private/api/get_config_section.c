#include <module/_private/_ddns.h>

bool PV_ddns_handleAPICall_get_config_section(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	if (!ddns_Config_write(
		&instance->config,
		request + 1,
		response
	)) {
		return false;
	}

	if (!napc_Writer_writeChar(response, 0)) {
		return false;
	}

	return true;
}