#if !defined(DDNS_STATISTICS_h)
	#define DDNS_STATISTICS_h

	#include <napc.h>

	// Type forwarding to avoid including "instance.h"
	// because instance.h includes this file
	typedef struct ddns__Instance ddns__Instance;

	typedef struct {
		bool is_valid;

		napc__DNSRequest dns_request;

		bool has_response;
		bool locally_resolved;
		napc__DNSResponse dns_response;

		bool has_timedout;

		napc_time _requested_at;
	} ddns__StatisticsDNSRequest;

	typedef struct {
		struct {
			napc_time                  uptime;
			napc_size                  error_count;
			signed long                upstream_latency;

			struct {
				napc_size total;
				napc_size served;
				napc_size timeout;
				napc_size invalid;
				napc_size throughput;
			} dns_requests_count;
		} persistent;

		napc_u16                   ticks_per_second;
		napc_i16                   tracked_metric_history[256];

		ddns__StatisticsDNSRequest _requests[8];
		napc__Timer                _1_second_timer;
		napc_size                  _throughput_counted_queries;
		napc_u16                   _tick_counter;
	} ddns__StatisticsContext;

	// only called ONCE in the program's lifecycle
	void ddns_Statistics_onBoot(ddns__Instance *instance);
	// called when ethernet link goes from DOWN->UP
	void ddns_Statistics_onLinkUp(ddns__Instance *instance);
	// called when ethernet link goes from UP->DOWN
	void ddns_Statistics_onLinkDown(ddns__Instance *instance);
	// continuously called when ethernet link is up
	void ddns_Statistics_loop(ddns__Instance *instance);


	void ddns_Statistics_registerDNSRequest(
		ddns__Instance *instance,
		const napc__DNSRequest *request,
		const napc_u8 *client_addr_ipv4
	);

	void ddns_Statistics_setDNSRequestTimeout(
		ddns__Instance *instance,
		napc_u16 dns_request_identifier
	);

	void ddns_Statistics_setDNSRequestResolved(
		ddns__Instance *instance,
		const napc__DNSResponse *response
	);

	void ddns_Statistics_setDNSRequestLocallyResolved(
		ddns__Instance *instance,
		napc_u16 dns_request_identifier,
		napc_size rd_data_length,
		const napc_u8 *rd_data
	);

	void ddns_Statistics_destroy(ddns__Instance *instance);
#endif
