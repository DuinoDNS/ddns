#if !defined(DDNS_CORE_h)
	#define DDNS_CORE_h

	#include <module/instance/instance.h>

	void ddns_setup(
		ddns__Instance *instance,
		const char *config_file_path,
		const char *records_file_path
	);

	void ddns_loop(ddns__Instance *instance);
#endif
