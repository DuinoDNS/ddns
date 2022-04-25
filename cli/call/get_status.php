<?php

function ddns__getStatusAPICall($ip, $port, $secret) {
	$response = ddns__sendRequest($ip, $port, $secret, "get_queries");
	$reader = new ddns__BinaryReader($response);

	var_dump($response);

	$uptime = $reader->readU32BE();
	$upstream_latency = $reader->readU32BE();
	if ($upstream_latency === 0xFFFFFFFF) {
		$upstream_latency = -1;
	}

	$dns_queries_total = $reader->readU32BE();
	$dns_queries_served = $reader->readU32BE();
	$dns_queries_timeout = $reader->readU32BE();
	$dns_queries_invalid = $reader->readU32BE();
	$dns_queries_throughput = $reader->readU32BE();
	$ticks_per_second = $reader->readU32BE();
	$random_bytes_available = $reader->readU32BE();

	$metric_type = $reader->readU32BE();
	$metric_values = [];
	$n_entries = $reader->readU16BE();

	for ($i = 0; $i < $n_entries; ++$i) {
		$metric_value = $reader->readU16BE();

		if ($metric_value === 0xFFFF) $metric_value = -1;

		array_push($metric_values, $metric_value);
	}

	return [
		"uptime" => $uptime,
		"upstream_latency" => $upstream_latency,
		"dns_queries" => [
			"total" => $dns_queries_total,
			"served" => $dns_queries_served,
			"timeout" => $dns_queries_timeout,
			"invalid" => $dns_queries_invalid,
			"throughput" => $dns_queries_throughput
		],
		"ticks_per_second" => $ticks_per_second,
		"random_bytes_available" => $random_bytes_available,
		"metric_type" => $metric_type,
		"metric_values" => $metric_values
	];
}

?>
