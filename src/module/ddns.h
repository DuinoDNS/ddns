#if !defined(DDNS_CORE_h)
	#define DDNS_CORE_h

	#include <napc.h>
	#include <module/config/config.h>
	#include <module/local-records/local-records.h>

	#define DDNS_QUERY_STATE_INITIALIZED 1
	#define DDNS_QUERY_STATE_COMPLETED   2
	#define DDNS_QUERY_STATE_TIMEOUT     3

	typedef struct {
		bool meta_initialized;

		struct {
			napc__DNSHeader dns_header;
			napc_time received_at;
			napc__IPv4Participant requester;
			napc_u8 state;
		} meta;

		bool has_request;
		napc__DNSRequest request;

		bool has_response;
		napc__DNSResponse response;
	} ddns__Query;

	typedef struct ddns__Instance {
		bool eth_link_status;
		ddns__Config config;
		ddns__LocalRecords local_records;

		bool debug_active;
		napc_size debug_log_handler_index;

		napc__Timer tmr;

		/**
		 * UDP Sockets
		 */
		napc__UDPSocket dns_udp_in;
		napc__UDPSocket networking_udp_out;
		napc__UDPSocket api_udp_in;

		/**
		 * Queries
		 */
		ddns__Query queries[4];

		/**
		 * Shared buffers
		 */
		char buffer_1k[1024];
		bool buffer_1k_busy;

		char buffer_4k[4096];
		bool buffer_4k_busy;
	} ddns__Instance;

	void ddns_setup(
		ddns__Instance *instance,
		const char *config_file_path,
		const char *records_file_path
	);

	void ddns_loop(ddns__Instance *instance);
#endif
