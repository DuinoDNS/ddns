#if !defined(PV_DDNS_API_LOG_h)
	#define PV_DDNS_API_LOG_h

	#define PV_DDNS_API_VERBOSE(...)  NAPC_LOG_VERBOSE("ddns_api", ##__VA_ARGS__)
	#define PV_DDNS_API_TRACE(...)    NAPC_LOG_TRACE("ddns_api", ##__VA_ARGS__)
	#define PV_DDNS_API_DEBUG(...)    NAPC_LOG_DEBUG("ddns_api", ##__VA_ARGS__)
	#define PV_DDNS_API_INFO(...)     NAPC_LOG_INFO("ddns_api", ##__VA_ARGS__)
	#define PV_DDNS_API_WARNING(...)  NAPC_LOG_WARNING("ddns_api", ##__VA_ARGS__)
	#define PV_DDNS_API_ERROR(...)    NAPC_LOG_ERROR("ddns_api", ##__VA_ARGS__)
	#define PV_DDNS_API_SECURITY(...) NAPC_LOG_SECURITY("ddns_api", ##__VA_ARGS__)
#endif
