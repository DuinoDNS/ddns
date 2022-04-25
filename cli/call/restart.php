<?php

function ddns__restartAPICall($ip, $port, $secret) {
	$response = ddns__sendRequest($ip, $port, $secret, "restart");

	var_dump($response);
}

?>
