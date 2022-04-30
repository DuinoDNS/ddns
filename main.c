#include <napc.h>
#include <ddns.h>

#if defined(ARDUINO)
	ddnsddns__Instance ddns_instance_obj;
#endif

ddns__Instance *ddns_instance_ptr = NULL;

void napc_app_setup(const char *platform) {
	NAPC_IGNORE_VALUE(platform);

	/*
	 * Use malloc() on linux to get diagnostics from valgrind
	 */
	#if defined(ARDUINO)
		ddns_instance_ptr = &ddns_instance_obj;
	#else
		ddns_instance_ptr = malloc(sizeof(* i));
	#endif

	ddns_setup(
		ddns_instance_ptr,
		"DUINODNS/CFG.TXT",
		"DUINODNS/RECORDS.TXT"
	);
}

bool napc_app_loop(napc_time uptime) {
	NAPC_IGNORE_VALUE(uptime);

	ddns_loop(ddns_instance_ptr);

	return true;
}
