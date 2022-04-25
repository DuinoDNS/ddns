#include <module/_private/_ddns.h>

void PV_ddns_printDebugInformation(ddns__Instance *instance) {
	if (!napc_Timer_expired(&instance->debug_print_timer)) {
		return;
	}

	napc_printf("\n\n");

	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(instance->queries); ++i) {
		ddns__Query *q = &instance->queries[i];

		napc_printf(
			"%3ld. %s %04x state %d",
			i+1,
			q->meta_initialized ? "meta initialized" : "                ",
			q->meta_initialized ? q->meta.dns_header.request_identifier : 0,
			q->meta_initialized ? q->meta.state : -1
		);

		if (q->meta_initialized && q->meta.state == DDNS_QUERY_STATE_INITIALIZED) {
			napc_printf(" INITIALIZED ");
		} else if (q->meta_initialized && q->meta.state == DDNS_QUERY_STATE_TIMEOUT) {
			napc_printf(" TIMEOUT ");

		} else if (q->meta_initialized && q->meta.state == DDNS_QUERY_STATE_COMPLETED) {
			napc_printf(" COMPLETED ");
		}

		if (q->meta_initialized) {
			if (q->has_request) {
				napc_printf(" HAS_REQUEST=yes ");
			}
			if (q->has_response) {
				napc_printf(" HAS_RESPONSE=yes ");
			}
		}

		napc_printf("\n");
	}

	napc_Timer_restart(&instance->debug_print_timer);
}
