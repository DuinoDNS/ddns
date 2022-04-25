#include <module/_private/_ddns.h>

void ddns_setup(
	ddns__Instance *instance,
	const char *config_file_path,
	const char *records_file_path
) {
	NAPC_IGNORE_VALUE(records_file_path);

	PV_DDNS_INFO("Initializing instance.");

	instance->eth_link_status = false;

	instance->debug_active = false;

	instance->buffer_1k_busy = false;
	instance->buffer_4k_busy = false;

	/**
	 * Set config defaults and then attempt to
	 * read configuration.
	 */
	ddns_Config_setDefaults(&instance->config);

	{
		if (napc_fs_readFileCString(config_file_path, instance->buffer_4k, sizeof(instance->buffer_4k))) {
			ddns_Config_fromString(&instance->config, instance->buffer_4k);
		}
	}

	{
		if (napc_fs_readFileCString(records_file_path, instance->buffer_4k, sizeof(instance->buffer_4k))) {
			ddns_LocalRecords_fromString(&instance->local_records, instance->buffer_4k);
		}
	}

	// dump configuration on start
	ddns_Config_dump(&instance->config);
	ddns_LocalRecords_dump(&instance->local_records);

	/**
	 * This function is only called ONCE in the program's lifecycle
	 */
	PV_ddns_onBoot(instance);
}