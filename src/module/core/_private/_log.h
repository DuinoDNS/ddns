#if !defined(PV_DDNS_LOG_h)
	#define PV_DDNS_LOG_h

	#define PV_DDNS_VERBOSE(...)  NAPC_LOG_VERBOSE("ddns", ##__VA_ARGS__)
	#define PV_DDNS_TRACE(...)    NAPC_LOG_TRACE("ddns", ##__VA_ARGS__)
	#define PV_DDNS_DEBUG(...)    NAPC_LOG_DEBUG("ddns", ##__VA_ARGS__)
	#define PV_DDNS_INFO(...)     NAPC_LOG_INFO("ddns", ##__VA_ARGS__)
	#define PV_DDNS_WARNING(...)  NAPC_LOG_WARNING("ddns", ##__VA_ARGS__)
	#define PV_DDNS_ERROR(...)    NAPC_LOG_ERROR("ddns", ##__VA_ARGS__)
	#define PV_DDNS_SECURITY(...) NAPC_LOG_SECURITY("ddns", ##__VA_ARGS__)
#endif
