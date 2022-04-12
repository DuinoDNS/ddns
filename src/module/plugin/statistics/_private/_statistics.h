#if !defined(PV_DDNS_STATISTICS_h)
	#define PV_DDNS_STATISTICS_h

	#include <module/plugin/statistics/statistics.h>
	#include <module/plugin/statistics/_private/_log.h>

	#include <module/instance/instance.h>

	void PV_ddns_Statistics_addValueToTrackedMetricHistory(
		ddns__Instance *instance
	);
#endif
