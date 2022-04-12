#include <module/core/_private/_core.h>

void ddns_setup(
	ddns__Instance *instance,
	const char *config_file_path,
	const char *records_file_path
) {
	NAPC_IGNORE_VALUE(records_file_path);

	PV_DDNS_INFO("Initializing instance.");

	instance->eth_link_status = false;
	instance->buffer_4k_1_busy = false;
	instance->buffer_4k_2_busy = false;

	/**
	 * Set config defaults and then attempt to
	 * read configuration.
	 */
	ddns_Config_setDefaults(&instance->config);

	{
		if (napc_fs_readFileCString(config_file_path, instance->buffer_4k_1, sizeof(instance->buffer_4k_1))) {
			ddns_Config_fromString(&instance->config, instance->buffer_4k_1);
		}
	}

	// dump configuration on start
	ddns_Config_dump(&instance->config);

	/**
	 * Initialize all plugins.
	 * These functions are only called ONCE in the program's lifecycle
	 */
	ddns_Network_onBoot(instance);
	ddns_Upstream_onBoot(instance);
	ddns_DNS_onBoot(instance);
	ddns_Statistics_onBoot(instance);
	ddns_API_onBoot(instance);
}
