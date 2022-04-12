#if !defined(PV_DDNS_API_h)
	#define PV_DDNS_API_h

	#include <module/plugin/api/api.h>
	#include <module/plugin/api/_private/_log.h>
	#include <module/plugin/api/_private/calls/calls.h>

	#include <module/instance/instance.h>

	void PV_ddns_API_handleUDPSocket(
		ddns__Instance *instance
	);

	void PV_ddns_API_handleAPIRequest(
		ddns__Instance *instance,
		napc__IPv4Participant source
	);

	bool PV_ddns_API_handleAPICall(
		ddns__Instance *instance,
		const char *request,
		napc__Writer *response
	);
#endif
