<?php

function ddns__sendRequest($ip, $port, $secret, $request_body) {
	$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);

	$request = ddns__encryptRequest($request_body, $secret);

	socket_sendto($socket, $request["message"], strlen($request["message"]), 0, $ip, $port);

	$answer = socket_read($socket, 1024);

	$response = ddns__decryptAnswer($answer, $secret);

	if ($response["request_identifier"] !== $request["request_identifier"]) {
		throw new Error("Request identifier do not match!");
	}

	return $response["message"];
}

?>
