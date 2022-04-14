<?php

function ddns__setDebugAPICall($ip, $port, $secret, $mode) {
	if ($mode) {
		$mode = "set";
	} else {
		$mode = "clear";
	}

	$response = ddns__sendRequest($ip, $port, $secret, "set_debug$mode");
	var_dump($response);
}

?>
