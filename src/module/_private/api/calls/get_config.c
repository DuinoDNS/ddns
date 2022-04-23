#include <module/_private/_ddns.h>

static char _tmp[256]; // @static

bool PV_ddns_handleAPICall_get_config(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	if (!ddns_Config_toString(
		&instance->config,
		false,
		_tmp,
		sizeof(_tmp)
	)) {
		return false;
	}

	if (!napc_Writer_writeString(response, _tmp)) {
		return false;
	}

	return true;
}
