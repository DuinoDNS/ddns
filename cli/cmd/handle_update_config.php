<?php

function handleUpdateConfig($ip, $port, $secret, $args) {
	if (sizeof($args["unnamed"]) !== 1) {
		throw new Exception("Config file missing.");
	}

	$config_file_contents = file_get_contents($args["unnamed"][0]);

	echo ddns__updateConfigAPICall($ip, $port, $secret, $config_file_contents);
}

?>
