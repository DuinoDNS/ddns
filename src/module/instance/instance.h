#if !defined(DDNS_INSTANCE_h)
	#define DDNS_INSTANCE_h

	#include <napc.h>

	#include <module/config/config.h>
	#include <module/local-records/local-records.h>
	#include <module/plugin/network/network.h>
	#include <module/plugin/upstream/upstream.h>
	#include <module/plugin/dns/dns.h>
	#include <module/plugin/statistics/statistics.h>
	#include <module/plugin/api/api.h>

	typedef struct ddns__Instance {
		bool eth_link_status;
		ddns__Config config;
		ddns__LocalRecords local_records;

		char buffer_1k[1024];
		bool buffer_1k_busy;

		char buffer_4k[4096];
		bool buffer_4k_busy;

		struct {
			ddns__NetworkContext network;
			ddns__UpstreamContext upstream;
			ddns__DNSContext dns;
			ddns__StatisticsContext statistics;
			ddns__APIContext api;
		} plugin;
	} ddns__Instance;

	/**
	 * Use a shared buffer identified by `label` for a fixed amount of time.
	 */
	void ddns_Instance_useSharedBuffer(
		ddns__Instance *instance, const char *label, void *context, void (*cb)(
			ddns__Instance *instance,
			void *context,
			napc__Buffer *buffer
		)
	);
#endif
