#include <module/_private/_ddns.h>

void PV_ddns_onBoot(ddns__Instance *instance) {
	napc_Timer_init(&instance->debug_print_timer, 1000);
	napc_Timer_start(&instance->debug_print_timer);
}