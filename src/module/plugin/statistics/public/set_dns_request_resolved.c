#include <module/plugin/statistics/_private/_statistics.h>

void ddns_Statistics_setDNSRequestResolved(
	ddns__Instance *instance,
	const napc__DNSResponse *response,
	bool locally_resolved
) {
	NAPC_IGNORE_VALUE(locally_resolved);

	ddns__StatisticsContext *ctx = &instance->plugin.statistics;

	ctx->persistent.dns_requests_count.served++;

	napc_u16 dns_request_identifier = response->header.request_identifier;

	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(ctx->_requests); ++i) {
		ddns__StatisticsDNSRequest *r = &ctx->_requests[i];

		// ignore invalid entries
		if (!r->is_valid) continue;
		if (r->dns_request.header.request_identifier != dns_request_identifier) continue;

		PV_DDNS_STATISTICS_DEBUG(
			"Setting req=%4.4x resolved", dns_request_identifier
		);

		r->has_response = true;
		r->dns_response = *response;

		return;
	}
}
