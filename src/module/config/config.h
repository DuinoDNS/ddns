#if !defined(DDNS_CONFIG_h)
	#define DDNS_CONFIG_h

	#include <napc.h>

	typedef struct {
		struct {
			char      secret[65];
			char      hashed_secret[65];
			bool      config_lock;
			napc_u16  tracked_metric;
		} general;

		struct {
			char      ip[NAPC_MODULE_NET_IP_STR_MAX];
			napc_u16  port;
			napc_u16  level;
		} debug;

		struct {
			char      mac_address[64];
			char      address[NAPC_MODULE_NET_IP_STR_MAX];
			char      netmask[NAPC_MODULE_NET_IP_STR_MAX];
			char      gateway[NAPC_MODULE_NET_IP_STR_MAX];
			napc_u16  out_port;
		} network;

		struct {
			bool      enabled;
			char      address[NAPC_MODULE_NET_IP_STR_MAX];
			napc_u16  port;
			napc_u16  ping_port;
			napc_u16  ping_interval;
			napc_u16  timeout;
		} upstream;

		struct {
			bool      enabled;
		} discovery;

		struct {
			bool      enabled;
			napc_u16  listen_port;
		} api;

		struct {
			napc_u16  listen_port;
			napc_u32  local_ttl;
		} dns;
	} ddns__Config;

	void ddns_Config_setDefaults(
		ddns__Config *config
	);

	void ddns_Config_fromString(
		ddns__Config *config,
		const char *string
	);

	void ddns_Config_dump(
		const ddns__Config *config
	);

	bool ddns_Config_toString(
		const ddns__Config *config,
		bool include_secret,
		char *buf,
		napc_size buf_size
	) NAPC_FN_WARNUNUSED_RET();
#endif
