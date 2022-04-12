#include <module/plugin/statistics/_private/_statistics.h>

void ddns_Statistics_loop(ddns__Instance *instance) {
	ddns__StatisticsContext *ctx = &instance->plugin.statistics;

	ctx->persistent.uptime = napc_getUptime();

	if (napc_Timer_expired(&ctx->_1_second_timer)) {
		napc_size throughput = ctx->_throughput_counted_queries;
		napc_size ticks = ctx->_tick_counter;

		// update ticks per second
		ctx->ticks_per_second = ticks;

		ctx->persistent.dns_requests_count.throughput = throughput;

		PV_DDNS_STATISTICS_VERBOSE(
			"Current throughput: %" NAPC_SIZE_PRINTF " q/s"
			" Ticks: %" NAPC_SIZE_PRINTF, throughput, ticks
		);

		ctx->_throughput_counted_queries = 0;
		ctx->_tick_counter = 0;

		PV_ddns_Statistics_addValueToTrackedMetricHistory(instance);
		napc_Timer_restart(&ctx->_1_second_timer);
	}

	ctx->_tick_counter++;
}
