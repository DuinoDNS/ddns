<?php

function ddns__getStatusAPICall($ip, $port, $secret) {
	$response = ddns__sendRequest($ip, $port, $secret, "get_status");
	$reader = new ddns__BinaryReader($response);

	$status = [];

	$status["debug_active"] = $reader->readU8() == 1;
	$status["incoming_queries"] = $reader->readU32BE();
	$status["completed_queries"] = $reader->readU32BE();
	$status["truncated_responses"] = $reader->readU32BE();

	$status["ticks_per_second"] = $reader->readU16BE();
	$status["queries_per_second"] = $reader->readU16BE();

	$status["random_bytes_available"] = $reader->readU16BE();
	$status["uptime"] = $reader->readU32BE();

	return $status;
}

?>
