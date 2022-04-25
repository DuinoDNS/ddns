#include <module/_private/_ddns.h>

static void _readConfigFile(
	ddns__Instance *instance,
	void *context,
	napc__Buffer *buffer
);

static void _readLocalRecordsFile(
	ddns__Instance *instance,
	void *context,
	napc__Buffer *buffer
);

void ddns_loop(ddns__Instance *instance) {
	if (instance->needs_initalisation) {
		PV_ddns_useSharedBuffer(instance, "1k-buffer-1", NULL, _readConfigFile);
		PV_ddns_useSharedBuffer(instance, "1k-buffer-1", NULL, _readLocalRecordsFile);

		// dump configuration on start
		ddns_Config_dump(&instance->config);
		ddns_LocalRecords_dump(&instance->local_records);

		instance->needs_initalisation = false;
	}

	bool eth_link_status = napc_eth_getLinkStatus();

	if (eth_link_status && !instance->eth_link_status) {
		PV_DDNS_INFO("Ethernet Link status changed from DOWN to UP.");

		PV_ddns_onLinkUp(instance);
	} else if (!eth_link_status && instance->eth_link_status) {
		PV_DDNS_INFO("Ethernet Link status changed from UP to DOWN.");

		PV_ddns_onLinkDown(instance);
	}

	if (eth_link_status) {
		PV_ddns_runLoop(instance);
	}

	instance->eth_link_status = eth_link_status;
}

static void _readConfigFile(
	ddns__Instance *instance,
	void *context,
	napc__Buffer *buffer
) {
	NAPC_IGNORE_VALUE(context);

	void *data = buffer->data;
	napc_size data_size = buffer->size;

	if (!napc_fs_readFileCString(instance->config_file_path,  data, data_size)) {
		return;
	}

	ddns_Config_fromString(&instance->config, data);
}

static void _readLocalRecordsFile(
	ddns__Instance *instance,
	void *context,
	napc__Buffer *buffer
) {
	NAPC_IGNORE_VALUE(context);

	void *data = buffer->data;
	napc_size data_size = buffer->size;

	if (!napc_fs_readFileCString(instance->records_file_path,  data, data_size)) {
		return;
	}

	ddns_LocalRecords_fromString(&instance->local_records, data);
}
