#include <module/plugin/statistics/_private/_statistics.h>

void ddns_Statistics_onLinkUp(ddns__Instance *instance) {
	ddns__StatisticsContext *ctx = &instance->plugin.statistics;

	ctx->ticks_per_second = 0;

	// init tracked metric history array
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(ctx->tracked_metric_history); ++i) {
		ctx->tracked_metric_history[i] = -1;
	}

	// init requests array
	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(ctx->_requests); ++i) {
		ddns__StatisticsDNSRequest *r = &ctx->_requests[i];

		r->is_valid = false;
		r->has_timedout = false;
		r->has_response = false;
	}

	napc_Timer_init(&ctx->_1_second_timer, 1000);
	napc_Timer_start(&ctx->_1_second_timer);

	ctx->_throughput_counted_queries = 0;
	ctx->_tick_counter = 0;
}
