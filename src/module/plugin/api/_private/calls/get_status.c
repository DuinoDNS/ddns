#include <module/plugin/api/_private/_api.h>

bool PV_ddns_API_handleAPICall_get_status(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	NAPC_IGNORE_VALUE(request);

	ddns__StatisticsContext *stats = &instance->plugin.statistics;

	if (!napc_Writer_writeU32BE(response, stats->persistent.uptime)) return false;

	napc_u32 upstream_latency = stats->persistent.upstream_latency > 0 ? stats->persistent.upstream_latency : NAPC_U32_LITERAL(0xFFFFFFFF);

	if (!napc_Writer_writeU32BE(response, upstream_latency)) return false;
	if (!napc_Writer_writeU32BE(response, stats->persistent.dns_requests_count.total)) return false;
	if (!napc_Writer_writeU32BE(response, stats->persistent.dns_requests_count.served)) return false;
	if (!napc_Writer_writeU32BE(response, stats->persistent.dns_requests_count.timeout)) return false;
	if (!napc_Writer_writeU32BE(response, stats->persistent.dns_requests_count.invalid)) return false;
	if (!napc_Writer_writeU32BE(response, stats->persistent.dns_requests_count.throughput)) return false;
	if (!napc_Writer_writeU32BE(response, stats->ticks_per_second)) return false;

	napc_size current_random_bytes_available = napc_random_getAvailableBytes();

	if (!napc_Writer_writeU32BE(response, current_random_bytes_available)) return false;

	// tracked metric
	if (!napc_Writer_writeU32BE(response, instance->config.general.tracked_metric)) return false;

	napc_size n_elements = NAPC_ARRAY_ELEMENTS(stats->tracked_metric_history);

	if (!napc_Writer_writeU16BE(response, n_elements)) return false;

	for (napc_size i = 0; i < n_elements; ++i) {
		napc_i16 tick_value = stats->tracked_metric_history[i];
		napc_u16 value = tick_value > 0 ? tick_value : NAPC_U16_LITERAL(0xFFFF);

		if (!napc_Writer_writeU16BE(response, value)) return false;
	}

	return true;
}
