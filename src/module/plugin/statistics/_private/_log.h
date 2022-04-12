#if !defined(PV_DDNS_STATISTICS_LOG_h)
	#define PV_DDNS_STATISTICS_LOG_h

	#define PV_DDNS_STATISTICS_VERBOSE(...)  NAPC_LOG_VERBOSE("ddns_stats", ##__VA_ARGS__)
	#define PV_DDNS_STATISTICS_TRACE(...)    NAPC_LOG_TRACE("ddns_stats", ##__VA_ARGS__)
	#define PV_DDNS_STATISTICS_DEBUG(...)    NAPC_LOG_DEBUG("ddns_stats", ##__VA_ARGS__)
	#define PV_DDNS_STATISTICS_INFO(...)     NAPC_LOG_INFO("ddns_stats", ##__VA_ARGS__)
	#define PV_DDNS_STATISTICS_WARNING(...)  NAPC_LOG_WARNING("ddns_stats", ##__VA_ARGS__)
	#define PV_DDNS_STATISTICS_ERROR(...)    NAPC_LOG_ERROR("ddns_stats", ##__VA_ARGS__)
	#define PV_DDNS_STATISTICS_SECURITY(...) NAPC_LOG_SECURITY("ddns_stats", ##__VA_ARGS__)
#endif
