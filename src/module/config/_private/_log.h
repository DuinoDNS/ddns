#if !defined(PV_DDNS_CONFIG_LOG_h)
	#define PV_DDNS_CONFIG_LOG_h

	#define PV_DDNS_CONFIG_VERBOSE(...)  NAPC_LOG_VERBOSE("ddns_config", ##__VA_ARGS__)
	#define PV_DDNS_CONFIG_TRACE(...)    NAPC_LOG_TRACE("ddns_config", ##__VA_ARGS__)
	#define PV_DDNS_CONFIG_DEBUG(...)    NAPC_LOG_DEBUG("ddns_config", ##__VA_ARGS__)
	#define PV_DDNS_CONFIG_INFO(...)     NAPC_LOG_INFO("ddns_config", ##__VA_ARGS__)
	#define PV_DDNS_CONFIG_WARNING(...)  NAPC_LOG_WARNING("ddns_config", ##__VA_ARGS__)
	#define PV_DDNS_CONFIG_ERROR(...)    NAPC_LOG_ERROR("ddns_config", ##__VA_ARGS__)
#endif
