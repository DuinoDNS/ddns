<?php

function ddns__updateConfigAPICall($ip, $port, $secret, $config_str) {
	$response = ddns__sendRequest($ip, $port, $secret, "update_config$config_str");

	var_dump($response);
}

?>
