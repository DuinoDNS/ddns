#if !defined(PV_DDNS_CONFIG_h)
	#define PV_DDNS_CONFIG_h

	#include <module/config/config.h>
	#include <module/config/_private/_log.h>

	/**
	 * Will be automatically created by create-config-handle-key-value.php
	 */
	bool PV_ddns_Config_handleKeyValue(
		ddns__Config *config,
		const char *key,
		const char *value
	);

	/**
	 * Will be automatically created by create-config-dump.php
	 */
	void PV_ddns_Config_dump(
		const ddns__Config *config
	);

	/**
	 * Will be automatically created by create-config-to-string.php
	 */
	bool PV_ddns_Config_toString(
		const ddns__Config *config,
		const char *desired_section,
		char *buf,
		napc_size buf_size
	);
#endif
