#if !defined(PV_DDNS_DNS_LOG_h)
	#define PV_DDNS_DNS_LOG_h

	#define PV_DDNS_DNS_VERBOSE(...)  NAPC_LOG_VERBOSE("duinodns_dns", ##__VA_ARGS__)
	#define PV_DDNS_DNS_TRACE(...)    NAPC_LOG_TRACE("duinodns_dns", ##__VA_ARGS__)
	#define PV_DDNS_DNS_DEBUG(...)    NAPC_LOG_DEBUG("duinodns_dns", ##__VA_ARGS__)
	#define PV_DDNS_DNS_INFO(...)     NAPC_LOG_INFO("duinodns_dns", ##__VA_ARGS__)
	#define PV_DDNS_DNS_WARNING(...)  NAPC_LOG_WARNING("duinodns_dns", ##__VA_ARGS__)
	#define PV_DDNS_DNS_ERROR(...)    NAPC_LOG_ERROR("duinodns_dns", ##__VA_ARGS__)
	#define PV_DDNS_DNS_SECURITY(...) NAPC_LOG_SECURITY("duinodns_dns", ##__VA_ARGS__)
#endif
