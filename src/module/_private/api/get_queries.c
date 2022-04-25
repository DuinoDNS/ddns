#include <module/_private/_ddns.h>

bool PV_ddns_handleAPICall_get_queries(
	ddns__Instance *instance,
	const char *request,
	napc__Writer *response
) {
	napc_Writer_writeU8(response, NAPC_ARRAY_ELEMENTS(instance->queries));

	for (napc_size i = 0; i < NAPC_ARRAY_ELEMENTS(instance->queries); ++i) {
		ddns__Query *q = &instance->queries[i];

		napc_Writer_writeChar(response, q->meta_initialized ? 'y' : 'n');

		if (!q->meta_initialized) continue;

		napc_Writer_writeU16BE(response, q->meta.dns_header.request_identifier);
		napc_Writer_writeU8(response, q->meta.state);

		napc_Writer_writeChar(response, q->has_request ? 'y' : 'n');

		if (!q->has_request) continue;

		napc_Writer_writeString(response, q->request.query.name);
		napc_Writer_writeChar(response, 0);
		napc_Writer_writeU8(response, q->request.query.qtype);
	}

	return true;
}
