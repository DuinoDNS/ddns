#include <module/config/_private/_config.h>

bool ddns_Config_toString(
	const ddns__Config *config,
	const char *desired_section,
	char *buf,
	napc_size buf_size
) {
	return PV_AGF_ddns_Config_toString(config, desired_section, buf, buf_size);
}
