#include <module/plugin/dns/_private/_dns.h>

static bool _resolveLocally(
	ddns__Instance *instance,
	napc__IPv4Participant client,
	napc__DNSRequest *dns_request
) {
	if (!dns_request) return false;

	const char *requested_name = dns_request->query.name;

	napc_ssize local_entry_index = ddns_LocalRecords_getEntryByNameAndType(
		&instance->local_records, requested_name, dns_request->query.qtype
	);

	if (0 > local_entry_index) return false;

	ddns__LocalDNSEntry *local_entry = &instance->local_records.entries[local_entry_index];

	PV_ddns_DNS_handleLocalDNSRequest(
		instance,
		&client,
		dns_request,
		local_entry
	);

	ddns_Statistics_setDNSRequestLocallyResolved(
		instance,
		dns_request->header.request_identifier,
		local_entry->rd_data_length,
		local_entry->rd_data
	);
}

void PV_ddns_DNS_handleDNSRequest(
	ddns__Instance *instance,
	napc__IPv4Participant client,
	napc__DNSRequest *dns_request,
	const char *buffer, napc_size buffer_size
) {
	if (_resolveLocally(instance, client, dns_request)) {
		PV_DDNS_DNS_INFO("Resolved DNS-request locally.");

		return;
	}

	PV_DDNS_DNS_DEBUG(
		"Cannot resolve name locally, trying to send to upstream (%s:%" NAPC_U16_PRINTF ")...",
		instance->config.upstream.address,
		instance->config.upstream.port
	);

	ddns_Upstream_sendRequest(instance, client, buffer, buffer_size);
}
