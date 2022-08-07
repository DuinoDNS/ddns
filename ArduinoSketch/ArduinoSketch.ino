#include <napc.h>
#include <ddns.h>

ddns__Instance i;

void napc_app_setup(const char *platform) {
	NAPC_IGNORE_VALUE(platform);

	ddns_setup(&i, "DUINODNS/CFG.TXT", "DUINODNS/RECORDS.TXT");
}

bool napc_app_loop(napc_time uptime) {
	NAPC_IGNORE_VALUE(uptime);

	ddns_loop(&i);

	return true;
}
