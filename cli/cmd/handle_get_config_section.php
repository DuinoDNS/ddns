<?php

function handleGetConfigSection($ip, $port, $secret, $args) {
	$config_section = ddns__getConfigSectionAPICall($ip, $port, $secret, $args["unnamed"][0]);

	if (!array_key_exists("--json", $args["named"])) {
		foreach ($config_section as $key => $value) {
			printf("%-30s %s\n", $key, $value);
		}

		return;
	}

	echo json_encode($config_section, JSON_PRETTY_PRINT)."\n";
}

?>
