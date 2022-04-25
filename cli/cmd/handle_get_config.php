<?php

function handleGetConfig($ip, $port, $secret, $args) {
	$config_sections = [
		"general", "debug", "network", "upstream", "api", "dns"
	];

	$config = [];

	foreach ($config_sections as $config_section) {
		$values = ddns__getConfigSectionAPICall($ip, $port, $secret, $config_section);

		foreach ($values as $key => $value) {
			$tmp = explode(".", $key, 2);

			$config[$config_section][$tmp[1]] = $value;
		}
	}

	if (!array_key_exists("--json", $args["named"])) {
		foreach ($config as $section => $values) {
			printf("\n* %s\n\n", $section);

			foreach ($values as $key => $value) {
				printf("    %-30s %s\n", $key, $value);
			}
		}

		return;
	}

	echo json_encode($config, JSON_PRETTY_PRINT)."\n";
}

?>
