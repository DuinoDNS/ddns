#include <module/_private/_ddns.h>

void ddns_setup(
	ddns__Instance *instance,
	const char *config_file_path,
	const char *records_file_path
) {
	PV_DDNS_INFO("Initializing instance.");

	/**
	 * Init core variables
	 */
	instance->eth_link_status = false;
	instance->debug_active = false;
	instance->buffer_1k_1_busy = false;
	instance->buffer_1k_2_busy = false;

	/**
	 * Set config defaults
	 */
	ddns_Config_setDefaults(&instance->config);

	instance->needs_initialization = true;
	instance->config_file_path = config_file_path;
	instance->records_file_path = records_file_path;

	instance->wants_reset = false;

	/**
	 * This function is only called ONCE in the program's lifecycle
	 */
	PV_ddns_onBoot(instance);
}
