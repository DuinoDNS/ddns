<?php

function ddns__getQueryHistoryAPICall($ip, $port, $secret) {
	$response = ddns__sendRequest($ip, $port, $secret, "get_query_history");
	$reader = new ddns__BinaryReader($response);

	$n_entries = $reader->readU8();
	$entries = [];

	for ($i = 0; $i < $n_entries; ++$i) {
		$dns_request_identifier = $reader->readU16BE();
		$label = $reader->readCString();
		$qtype = $reader->readU16BE();
		$client_ip = $reader->readU8Array(4);
		$has_response = !!$reader->readU8();
		$has_timedout = !!$reader->readU8();

		$response = null;

		if ($has_response) {
			$resolved_to_valid = !!$reader->readU8();
			$resolved_to_ipv6 = !!$reader->readU8();
			$resolved_to = $reader->readU8Array(16);
			$dns_response_code = $reader->readU16BE();

			$response = [
				"dns_response_code" => $dns_response_code
			];

			if ($resolved_to_valid) {
				if ($resolved_to_ipv6) {
					$response["resolved_to"] = duinodns__IPv6AddressToString($resolved_to);
				} else {
					$response["resolved_to"] = duinodns__IPv4AddressToString($resolved_to);
				}
			}
		}

		$status = "U";

		if ($has_response) {
			$status = "R";
		} else if ($has_timedout) {
			$status = "T";
		}

		array_push(
			$entries,
			[
				"dns_request_identifier" => $dns_request_identifier,
				"label" => $label,
				"type" => duinodns__QTypeToString($qtype),
				"client_ip" => duinodns__IPv4AddressToString($client_ip),
				"response" => $response,
				"timeout" => $has_timedout,
				"status" => $status
			]
		);
	}

	return $entries;
}

?>
