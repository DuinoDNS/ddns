#if !defined(PV_DDNS_CORE_h)
	#define PV_DDNS_CORE_h

	#include <module/ddns.h>

	#define PV_DDNS_VERBOSE(...)  NAPC_LOG_VERBOSE("ddns", ##__VA_ARGS__)
	#define PV_DDNS_TRACE(...)    NAPC_LOG_TRACE("ddns", ##__VA_ARGS__)
	#define PV_DDNS_DEBUG(...)    NAPC_LOG_DEBUG("ddns", ##__VA_ARGS__)
	#define PV_DDNS_INFO(...)     NAPC_LOG_INFO("ddns", ##__VA_ARGS__)
	#define PV_DDNS_WARNING(...)  NAPC_LOG_WARNING("ddns", ##__VA_ARGS__)
	#define PV_DDNS_ERROR(...)    NAPC_LOG_ERROR("ddns", ##__VA_ARGS__)
	#define PV_DDNS_SECURITY(...) NAPC_LOG_SECURITY("ddns", ##__VA_ARGS__)

	void PV_ddns_onBoot(ddns__Instance *instance);
	void PV_ddns_onLinkUp(ddns__Instance *instance);
	void PV_ddns_onLinkDown(ddns__Instance *instance);
	void PV_ddns_runLoop(ddns__Instance *instance);

	/**
	 * DNS
	 */
	void PV_ddns_handleDNSUDPMessage(
		ddns__Instance *instance, napc__IPv4Participant *client, napc__Buffer buffer
	);

	ddns__Query *PV_ddns_getQueryByRequestIdentifier(
		ddns__Instance *instance, napc_u16 dns_request_identifier
	);

	void PV_ddns_sendDNSQueryAnswer(
		ddns__Instance *instance,
		napc__IPv4Participant *client,
		ddns__Query *query,
		ddns__LocalDNSEntry *entry
	);

	/**
	 * Networking / Uptream
	 */
	void PV_ddns_handleNetworkingUDPMessage(
		ddns__Instance *instance, napc__IPv4Participant *client, napc__Buffer buffer
	);

	/**
	 * API
	 */
	void PV_ddns_handleAPIUDPMessage(
		ddns__Instance *instance, napc__IPv4Participant *client, napc__Buffer buffer
	);
#endif
