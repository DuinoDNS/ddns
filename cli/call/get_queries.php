<?php

function ddns__getQueriesAPICall($ip, $port, $secret) {
	$response = ddns__sendRequest($ip, $port, $secret, "get_queries");
	$reader = new ddns__BinaryReader($response);

	$incoming_queries = $reader->readU32BE();
	$completed_queries = $reader->readU32BE();

	$n_entries = $reader->readU8();
	$entries = [];

	for ($i = 0; $i < $n_entries; ++$i) {
		$meta_initialized = $reader->readChar() === "y";

		if (!$meta_initialized) continue;

		$request_identifier = $reader->readU16BE();
		$state = "unknown";

		switch ($reader->readU8()) {
			case 1: $state = "initialized"; break;
			case 2: $state = "completed"; break;
			case 3: $state = "timeout"; break;
		}

		$query_latency = NULL;
		if ($state === "completed") {
			$query_latency = $reader->readU32BE();
		}

		$has_request = $reader->readChar() === "y";
		$request = NULL;

		if ($has_request) {
			$request = [];

			$request["name"] = $reader->readCString();
			$request["qtype"] = $reader->readU8();
			$request["qtype_str"] = ddns__QTypeToString($request["qtype"]);
		}

		$entries[] = [
			"request_identifier" => $request_identifier,
			"state" => $state,
			"request" => $request,
			"query_latency" => $query_latency
		];
	}

	return [
		"incoming" => $incoming_queries,
		"completed" => $completed_queries,
		"entries" => $entries
	];
}

?>
