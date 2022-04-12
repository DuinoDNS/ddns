#include <module/plugin/statistics/_private/_statistics.h>

void ddns_Statistics_registerDNSRequest(
	ddns__Instance *instance,
	const napc__DNSRequest *request,
	const napc_u8 *client_addr_ipv4
) {
	NAPC_IGNORE_VALUE(client_addr_ipv4);

	ddns__StatisticsContext *ctx = &instance->plugin.statistics;

	ctx->_throughput_counted_queries++;
	ctx->persistent.dns_requests_count.total++;

	napc_misc_shiftArrayRight(
		ctx->_requests,
		NAPC_ARRAY_ELEMENTS(ctx->_requests),
		sizeof(* ctx->_requests)
	);

	ddns__StatisticsDNSRequest *head = &ctx->_requests[0];

	head->is_valid = true;
	head->has_response = false;
	head->has_timedout = false;
	head->_requested_at = napc_getTimeSinceBoot();

	head->dns_request = *request;

	PV_DDNS_STATISTICS_DEBUG(
		"Init req=%4.4x", request->header.request_identifier
	);
}
