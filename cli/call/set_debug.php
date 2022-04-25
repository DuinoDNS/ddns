<?php

function ddns__setDebugAPICall($ip, $port, $secret, $mode) {
	if ($mode) {
		$mode = "set_debug";
	} else {
		$mode = "clear_debug";
	}

	$response = ddns__sendRequest($ip, $port, $secret, $mode);
	var_dump($response);
}

?>
