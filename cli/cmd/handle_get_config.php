<?php

function handleGetConfig($ip, $port, $secret, $args) {
	$config = ddns__getConfigAPICall($ip, $port, $secret);

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
