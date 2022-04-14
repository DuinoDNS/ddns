<?php

function ddns_cli_main($args) {
	array_shift($args);

	if (!sizeof($args)) {
		fwrite(STDERR, "Usage: ddns <call> [args]\n");
		fwrite(STDERR, "\n");
		fwrite(STDERR, "       ddns get_status --target ip:port --secret /path/to/secret [--json]\n");

		fwrite(STDERR, "\n");
		fwrite(STDERR, "       ddns get_config --target ip:port --secret /path/to/secret [--json]\n");

		exit(2);
	}

	$target_ip = NULL;
	$target_port = NULL;
	$secret = NULL;
	$wants_json = false;

	$api_call = array_shift($args);

	while (sizeof($args)) {
		$arg = array_shift($args);

		switch ($arg) {
			case "--target": {
				$target = array_shift($args);

				if (!$target) {
					throw new Error("--target: value required.");
				}

				$tmp = explode(":", $target, 2);

				if (sizeof($tmp) !== 2) {
					throw new Error("--target: invalid format expected 'ip:port'.");
				}

				$target_ip = $tmp[0];
				$target_port = (int)$tmp[1];
			} break;

			case "--secret": {
				$secret_file_path = array_shift($args);

				if (!$secret_file_path) {
					throw new Error("--secret: value required.");
				} else if (!is_readable($secret_file_path) || !is_file($secret_file_path)) {
					throw new Error("--secret: file is not readable");
				}

				$secret = trim(file_get_contents($secret_file_path));
			} break;

			case "--json": {
				$wants_json = true;
			} break;
		}
	}

	if (!$target_ip) {
		throw new Error("--target is missing.");
	} else if (!$secret) {
		throw new Error("--secret is missing.");
	}

	switch ($api_call) {
		case "get_status": {
			handleGetStatus(
				$target_ip, $target_port, $secret, $wants_json
			);
		} break;

		case "get_qhistory": {
			handleGetQHistory(
				$target_ip, $target_port, $secret, $wants_json
			);
		} break;

		case "set_debug": {
			handleSetDebug(
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
