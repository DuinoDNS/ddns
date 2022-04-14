#if !defined(PV_DDNS_UPSTREAM_LOG_h)
	#define PV_DDNS_UPSTREAM_LOG_h

	#define PV_DDNS_UPSTREAM_VERBOSE(...)  NAPC_LOG_VERBOSE("ddns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_TRACE(...)    NAPC_LOG_TRACE("ddns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_DEBUG(...)    NAPC_LOG_DEBUG("ddns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_INFO(...)     NAPC_LOG_INFO("ddns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_WARNING(...)  NAPC_LOG_WARNING("ddns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_ERROR(...)    NAPC_LOG_ERROR("ddns_upstream", ##__VA_ARGS__)
	#define PV_DDNS_UPSTREAM_SECURITY(...) NAPC_LOG_SECURITY("ddns_upstream", ##__VA_ARGS__)
#endif
