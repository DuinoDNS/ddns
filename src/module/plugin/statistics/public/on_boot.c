#include <module/plugin/statistics/_private/_statistics.h>

void ddns_Statistics_onBoot(ddns__Instance *instance) {
	ddns__StatisticsContext *ctx = &instance->plugin.statistics;

	ctx->persistent.uptime = 0;
	ctx->persistent.error_count = 0;
	ctx->persistent.upstream_latency = -1;

	ctx->persistent.dns_requests_count.total = 0;
	ctx->persistent.dns_requests_count.served = 0;
	ctx->persistent.dns_requests_count.timeout = 0;
	ctx->persistent.dns_requests_count.invalid = 0;
	ctx->persistent.dns_requests_count.throughput = 0;
}
