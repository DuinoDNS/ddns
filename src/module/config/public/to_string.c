#include <module/config/_private/_config.h>

bool ddns_Config_toString(
	const ddns__Config *config,
	bool include_secret,
	char *buf,
	napc_size buf_size
) {
	return PV_ddns_Config_toString(config, include_secret, buf, buf_size);
}
