<?php

function handleGetQueries($ip, $port, $secret, $args) {
	$queries = ddns__getQueriesAPICall($ip, $port, $secret);

	if (!array_key_exists("--json", $args["named"])) {
		printf("\nQueries (completed / incoming) : %d / %d\n", $queries["completed"], $queries["incoming"]);

		$reliability = 0;

		if ($queries["completed"] > 0) {
			$reliability = (int)(($queries["incoming"] / $queries["completed"]) * 100);
		}

		printf("Reliability (%%)                : %3d %%\n\n", $reliability);

		$fmt = "%3s %s | %s | %s | %s | %s\n";

		$paddings = [18, 16, 40, 32, 16];

		$pad = function($index, $str) use ($paddings) {
			$pad_to = $paddings[$index];
			$delta = $pad_to - strlen($str);

			if (0 >= $delta) return $str;

			return str_pad($str, $pad_to, " ", STR_PAD_LEFT);
		};

		printf("\033[0;90m");
		printf(
			$fmt,
			"",
			$pad(0, "Request Identifier"),
			$pad(1, "Status"),
			$pad(2, "Request (name)"),
			$pad(3, "Request (type)"),
			$pad(4, "Latency")
		);
		printf("\033[0;0m");

		$i = 1;

		foreach ($queries["entries"] as $query) {
			$request_name = "-";
			$request_type = "-";

			if ($query["request"] !== NULL) {
				$request_name = $query["request"]["name"];
				$request_type = $query["request"]["qtype_str"];
			}

			$colorized_state = $pad(1, $query["state"]);

			if ($query["state"] === "completed") {
				$colorized_state = ddns_green(
					$pad(1, $query["state"])
				);
			} else if ($query["state"] === "timeout") {
				$colorized_state = ddns_yellow(
					$pad(1, $query["state"])
				);
			}

			$latency = $query["query_latency"] !== NULL ? $query["query_latency"]."ms" : "-";

			$request_identifier = dechex($query["request_identifier"]);
			$request_identifier = str_pad($request_identifier, 4, "0", STR_PAD_LEFT);

			printf(
				$fmt,
				"$i",
				ddns_gray($pad(0, $request_identifier)),
				$colorized_state,
				$pad(2, $request_name),
				ddns_gray($pad(3, $request_type)),
				ddns_gray($pad(4, $latency))
			);

			++$i;
		}

		return;
	}

	echo json_encode($queries, JSON_PRETTY_PRINT)."\n";
}

?>
