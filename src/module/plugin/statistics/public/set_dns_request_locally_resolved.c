#include <module/plugin/statistics/_private/_statistics.h>

void ddns_Statistics_setDNSRequestLocallyResolved(
	ddns__Instance *instance,
	napc_u16 dns_request_identifier,
	napc_size rd_data_length,
	const napc_u8 *rd_data
) {
	ddns__StatisticsContext *ctx = &instance->plugin.statistics;

	ctx->persistent.dns_requests_count.served++;

	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(ctx->_requests); ++i) {
		ddns__StatisticsDNSRequest *r = &ctx->_requests[i];

		// ignore invalid entries
		if (!r->is_valid) continue;
		if (r->dns_request.header.request_identifier != dns_request_identifier) continue;

		PV_DDNS_STATISTICS_DEBUG(
			"Setting req=%4.4x resolved", dns_request_identifier
		);

		//napc__DNSResponse mock_response;

		r->has_response = false;
		//r->dns_response = *response;
		r->locally_resolved = true;

		return;
	}
}
