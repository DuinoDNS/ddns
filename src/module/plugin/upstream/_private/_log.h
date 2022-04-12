#if !defined(PV_DDNS_UPSTREAM_LOG_h)
	#define PV_DDNS_UPSTREAM_LOG_h

	#define PV_DDNS_UPSTREAM_VERBOSE(...)  NAPC_LOG_VERBOSE("duinodns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_TRACE(...)    NAPC_LOG_TRACE("duinodns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_DEBUG(...)    NAPC_LOG_DEBUG("duinodns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_INFO(...)     NAPC_LOG_INFO("duinodns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_WARNING(...)  NAPC_LOG_WARNING("duinodns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_ERROR(...)    NAPC_LOG_ERROR("duinodns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_SECURITY(...) NAPC_LOG_SECURITY("duinodns_upstream", ##__VA_ARGS__)
#endif
