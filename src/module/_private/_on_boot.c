#include <module/_private/_ddns.h>

void PV_ddns_onBoot(ddns__Instance *instance) {
	napc_Timer_init(&instance->tmr, 1000);
	napc_Timer_start(&instance->tmr);
}
