<?php

function handleGetQueries($ip, $port, $secret, $wants_json) {
	$queries = ddns__getQueriesAPICall($ip, $port, $secret);

	if (!$wants_json) {
		printf("\nQueries (completed / incoming) : %d / %d\n", $queries["completed"], $queries["incoming"]);
		printf("Reliability (%%)                : %3d %%\n\n", (int)(($queries["incoming"] / $queries["completed"]) * 100));

		$fmt = "%3s %-18s | %-16s | %-40s | %-16s\n";

		printf(
			$fmt,
			"",
			"Request Identifier",
			"Status",
			"Request (name)",
			"Request (type)"
		);

		$i = 1;

		foreach ($queries["entries"] as $query) {
			$request_name = "-";
			$request_type = "-";

			if ($query["request"] !== NULL) {
				$request_name = $query["request"]["name"];
				$request_type = $query["request"]["qtype_str"];
			}

			printf(
				$fmt,
				"$i",
				dechex($query["request_identifier"]),
				$query["state"],
				$request_name,
				$request_type
			);

			++$i;
		}

		return;
	}

	echo json_encode($queries, JSON_PRETTY_PRINT)."\n";
}

?>
