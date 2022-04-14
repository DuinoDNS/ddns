#include <module/plugin/api/_private/_api.h>

static char _debug_message[512];

static void _logHandler(
	void *context,
	const char *subsys, int level, const char *fn, const char *msg
) {
	ddns__Instance *instance = context;

	napc__IPv4Participant destination = napc_IPv4Participant_create(
		instance->config.debug.ip, instance->config.debug.port
	);

	napc_snprintf(
		_debug_message,
		sizeof(_debug_message),
		"log,%s,%d,%s,%s\n",
		subsys, level, fn, msg
	);

	ddns_Network_sendSilent(
		instance,
		destination,
		_debug_message,
		napc_strlen(_debug_message)
	);
}

bool PV_ddns_API_handleAPICall_set_debug(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	if (napc_streqli(request, "clear") && instance->debug_active) {
		napc_printf("Clear debug request\n");

		instance->debug_active = false;

		napc_removeLogHandlerFunction(instance->debug_log_handler_index);

		napc_Writer_writeString(response, "debugging disabled\n");
	} else if (napc_streqli(request, "set") && !instance->debug_active) {
		napc_printf("Set debug request\n");

		instance->debug_active = true;

		/**
		 * Install global log handler
		 */
		instance->debug_log_handler_index = napc_addLogHandlerFunction(
			_logHandler, instance
		);

		napc_Writer_writeString(response, "debugging enabled\n");
	} else {
		napc_Writer_writeString(response, "what?\n");
	}

	return true;
}
