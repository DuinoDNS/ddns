<?php

function ddns__getTrackedMetricAPICall($ip, $port, $secret) {
	$response = ddns__sendRequest($ip, $port, $secret, "get_tracked_metric");
	$reader = new ddns__BinaryReader($response);

	$ret = [
		"kind" => "?",
		"values" => []
	];

	$tracked_metric = $reader->readU16BE();

	switch ($tracked_metric) {
		case 1: $ret["kind"] = "tps"; break;
		case 2: $ret["kind"] = "upstream_latency"; break;
	}

	$n_entries = $reader->readU16BE();

	for ($i = 0; $i < $n_entries; ++$i) {
		$value = $reader->readU16BE();

		if ($value == 0xFFFF) $value = -1;

		$ret["values"][] = $value;
	}

	return $ret;
}

?>
