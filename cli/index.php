<?php

function ddns_cli_main($args) {
	array_shift($args);

	if (2 >= sizeof($args)) {
		fwrite(STDERR, "Usage: ddns <target> <secret> <cmd> [args]\n");
		fwrite(STDERR, "\n");
		fwrite(STDERR, "       ddns ip:port /path/to/secret get_status [--json]\n");
		fwrite(STDERR, "       ddns ip:port /path/to/secret get_queries [--json]\n");
		fwrite(STDERR, "       ddns ip:port /path/to/secret get_config [--json]\n");
		fwrite(STDERR, "\n");
		fwrite(STDERR, "       ddns ip:port /path/to/secret set_debug\n");
		fwrite(STDERR, "       ddns ip:port /path/to/secret clear_debug\n");

		exit(2);
	}

	$target = array_shift($args);
	$tmp = explode(":", $target, 2);

	if (sizeof($tmp) === 2) {
		$target_ip = $tmp[0];
		$target_port = (int)$tmp[1];
	} else {
		$target_ip = $tmp[0];
		$target_port = 9090;
	}

	$secret_file_path = array_shift($args);

	if (!is_readable($secret_file_path) || !is_file($secret_file_path)) {
		throw new Error("secret file is not readable");
	}

	$secret = trim(file_get_contents($secret_file_path));

	$api_call = array_shift($args);
	$wants_json = false;

	switch ($api_call) {
		case "get_status": {
			handleGetStatus(
				$target_ip, $target_port, $secret, $wants_json
			);
		} break;

		case "get_queries": {
			handleGetQueries(
				$target_ip, $target_port, $secret, $wants_json
			);
		} break;

		case "set_debug": {
			handleSetDebug(
				$target_ip, $target_port, $secret, $wants_json
			);
		} break;

		case "clear_debug": {
			handleClearDebug(
				$target_ip, $target_port, $secret, $wants_json
			);
		} break;
	}
}

try {
	ddns_cli_main($argv);
} catch (Error $e) {
	fwrite(STDERR, $e->getMessage()."\n");
	exit(1);
}

?>
