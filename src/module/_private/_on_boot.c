#include <module/_private/_ddns.h>

void PV_ddns_onBoot(ddns__Instance *instance) {
	napc_Timer_init(&instance->debug_print_timer, 2500);
	napc_Timer_start(&instance->debug_print_timer);

	napc_Timer_init(&instance->network_advertisement_timer, 5000);
}
