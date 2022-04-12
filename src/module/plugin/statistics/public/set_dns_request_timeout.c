#include <module/plugin/statistics/_private/_statistics.h>

void ddns_Statistics_setDNSRequestTimeout(
	ddns__Instance *instance,
	napc_u16 dns_request_identifier
) {
	ddns__StatisticsContext *ctx = &instance->plugin.statistics;

	ctx->persistent.dns_requests_count.timeout++;

	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(ctx->_requests); ++i) {
		ddns__StatisticsDNSRequest *r = &ctx->_requests[i];

		// ignore invalid entries
		if (!r->is_valid) continue;
		if (r->dns_request.header.request_identifier != dns_request_identifier) continue;

		PV_DDNS_STATISTICS_DEBUG(
			"Setting req=%4.4x timeout", dns_request_identifier
		);

		r->has_timedout = true;

		return;
	}

	PV_DDNS_STATISTICS_ERROR(
		"Unknown request req=%4.4x", dns_request_identifier
	);
}
