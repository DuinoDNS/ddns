<?php

function ddns__getConfigAPICall($ip, $port, $secret) {
	$response = ddns__sendRequest($ip, $port, $secret, "get_config");
	$reader = new ddns__BinaryReader($response);
	$string = $reader->readCString();
	$config = [];

	foreach (explode("\n", $string) as $line) {
		$tmp = explode(",", $line, 2);

		if (sizeof($tmp) !== 2) continue;

		$config_key = $tmp[0];
		$config_value = $tmp[1];

		$tmp = explode(".", $config_key, 2);

		if (sizeof($tmp) !== 2) continue;

		$config_section = $tmp[0];
		$config_section_key = $tmp[1];

		if (!array_key_exists($config_section, $config)) {
			$config[$config_section] = [];
		}

		$config[$config_section][$config_section_key] = $config_value;
	}

	return $config;
}

?>
