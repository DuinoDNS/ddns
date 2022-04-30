<?php

function ddns_gray($str) {
	return "\033[0;90m$str\033[0;0m";
}

function ddns_cyan($str) {
	return "\033[1;36m$str\033[0;0m";
}

function ddns_cli_main($args) {
	array_shift($args);

	if (2 >= sizeof($args)) {
		fwrite(STDERR, "Usage: ddns ip[:port] /path/to/secret <cmd> [args]\n");
		fwrite(STDERR, "\n    Status\n\n");
		fwrite(STDERR, "           ddns ".ddns_gray("ip[:port] /path/to/secret")." ".ddns_cyan("get_status")." [--json]\n");
		fwrite(STDERR, "           ddns ".ddns_gray("ip[:port] /path/to/secret")." ".ddns_cyan("get_queries")." [--json]\n");
		fwrite(STDERR, "\n    Configuration\n\n");
		fwrite(STDERR, "           ddns ".ddns_gray("ip[:port] /path/to/secret")." ".ddns_cyan("get_config")." [--json]\n");
		fwrite(STDERR, "           ddns ".ddns_gray("ip[:port] /path/to/secret")." ".ddns_cyan("update_config")." /path/to/config\n");
		fwrite(STDERR, "\n    Debugging\n\n");
		fwrite(STDERR, "           ddns ".ddns_gray("ip[:port] /path/to/secret")." ".ddns_cyan("set_debug")."\n");
		fwrite(STDERR, "           ddns ".ddns_gray("ip[:port] /path/to/secret")." ".ddns_cyan("clear_debug")."\n");
		fwrite(STDERR, "           ddns ".ddns_gray("ip[:port] /path/to/secret")." ".ddns_cyan("restart")."\n");
		fwrite(STDERR, "\n");

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

	$api_call_args = [
		"named" => [],
		"unnamed" => []
	];

	// parse additional args
	while (true) {
		$arg = array_shift($args);

		if (!$arg) break;

		if (substr($arg, 0, 2) === "--") {
			$api_call_args["named"][$arg] = array_shift($args);
		} else {
			$api_call_args["unnamed"][] = $arg;
		}
	}

	switch ($api_call) {
		case "get_status": {
			handleGetStatus(
				$target_ip, $target_port, $secret, $api_call_args
			);
		} break;

		case "get_config": {
			handleGetConfig(
				$target_ip, $target_port, $secret, $api_call_args
			);
		} break;

		case "update_config": {
			handleUpdateConfig(
				$target_ip, $target_port, $secret, $api_call_args
			);
		} break;

		case "get_queries": {
			handleGetQueries(
				$target_ip, $target_port, $secret, $api_call_args
			);
		} break;

		case "get_tracked_metric": {
			handleGetTrackedMetric(
				$target_ip, $target_port, $secret, $api_call_args
			);
		} break;

		case "restart": {
			handleRestart(
				$target_ip, $target_port, $secret, $api_call_args
			);
		} break;

		case "set_debug": {
			handleSetDebug(
				$target_ip, $target_port, $secret, $api_call_args
			);
		} break;

		case "clear_debug": {
			handleClearDebug(
				$target_ip, $target_port, $secret, $api_call_args
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
