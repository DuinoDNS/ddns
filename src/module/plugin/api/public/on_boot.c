#include <module/plugin/api/_private/_api.h>

void ddns_API_onBoot(ddns__Instance *instance) {
	ddns__APIContext *ctx = &instance->plugin.api;

	NAPC_IGNORE_VALUE(ctx);
}
