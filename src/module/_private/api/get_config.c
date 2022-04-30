#include <module/_private/_ddns.h>

static const char *_sections[7] = {
	"general", "debug", "network", "upstream", "api", "discovery", "dns"
}; // @static

bool PV_ddns_handleAPICall_get_config(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(_sections); ++i) {
		bool result = ddns_Config_write(
			&instance->config, _sections[i], response
		);

		if (!result) return false;
	}

	return true;
}
