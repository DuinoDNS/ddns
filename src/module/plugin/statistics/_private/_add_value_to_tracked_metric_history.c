#include <module/plugin/statistics/_private/_statistics.h>

void PV_ddns_Statistics_addValueToTrackedMetricHistory(
	ddns__Instance *instance
) {
	ddns__StatisticsContext *ctx = &instance->plugin.statistics;

	napc_i16 metric_value = -1;

	switch (instance->config.general.tracked_metric) {
		//  (0 = tps, 1 = q/s, 2 = upstream_latency)
		// ticks per second
		case 0: {
			metric_value = ctx->ticks_per_second;
		} break;

		// query throughput
		case 1: {
			metric_value = ctx->persistent.dns_requests_count.throughput;
		} break;

		// upstream latency
		case 2: {
			if (0 > ctx->persistent.upstream_latency) {
				metric_value = -1;
			} else {
				metric_value = (napc_i16)ctx->persistent.upstream_latency;
			}
		} break;

		default:
			PV_DDNS_STATISTICS_ERROR("Unknown tracked metric '%" NAPC_U16_PRINTF "'", instance->config.general.tracked_metric);
	}

	napc_misc_shiftArrayRight(
		ctx->tracked_metric_history,
		NAPC_ARRAY_ELEMENTS(ctx->tracked_metric_history),
		sizeof(* ctx->tracked_metric_history)
	);

	ctx->tracked_metric_history[0] = metric_value;
}
