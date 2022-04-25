#include <module/_private/_ddns.h>

void PV_ddns_gatherStatisticalValues(ddns__Instance *instance) {
	++instance->stats._current_ticks_count;

	if (!napc_Timer_expired(&instance->statistics_timer)) {
		return;
	}

	instance->stats.ticks_per_second = instance->stats._current_ticks_count;
	instance->stats._current_ticks_count = 0;

	napc_Timer_restart(&instance->statistics_timer);
}
