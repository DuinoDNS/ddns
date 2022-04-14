<?php

function ddns__setConfigAPICall($ip, $port, $password, $config) {
	$response = ddns__sendRequest($ip, $port, $password, "set_config$config");
	var_dump($response);
}

?>
