<?php

function ddns__getStatusAPICall($ip, $port, $secret) {
	$response = ddns__sendRequest($ip, $port, $secret, "get_status");
	$reader = new ddns__BinaryReader($response);

/*
	napc_Writer_writeU32BE(response, instance->stats.incoming_queries);
	napc_Writer_writeU32BE(response, instance->stats.completed_queries);

	napc_Writer_writeU16BE(response, instance->stats.ticks_per_second);
	napc_Writer_writeU16BE(response, instance->stats.queries_per_second);

	napc_u16 random_bytes_available = napc_random_getAvailableBytes();

	napc_Writer_writeU16BE(response, random_bytes_available);
	napc_Writer_writeU32BE(response, napc_getUptime());
*/

	$status = [];

	$status["incoming_queries"] = $reader->readU32BE();
	$status["completed_queries"] = $reader->readU32BE();

	$status["ticks_per_second"] = $reader->readU16BE();
	$status["queries_per_second"] = $reader->readU16BE();

	$status["random_bytes_available"] = $reader->readU16BE();
	$status["uptime"] = $reader->readU32BE();

	return $status;
}

?>
