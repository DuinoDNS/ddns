<?php

function ddns__getConfigSectionAPICall($ip, $port, $secret, $section) {
	$response = ddns__sendRequest($ip, $port, $secret, "get_config_section:$section");
	$reader = new ddns__BinaryReader($response);
	$string = $reader->readCString();
	$values = [];

	foreach (explode("\n", $string) as $line) {
		$tmp = explode(",", $line, 2);

		if (sizeof($tmp) !== 2) continue;

		$values[$tmp[0]] = $tmp[1];
	}

	return $values;
}

?>
