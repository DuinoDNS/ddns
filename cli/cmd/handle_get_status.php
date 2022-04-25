<?php

function handleGetStatus($ip, $port, $secret, $args) {
	$status = ddns__getStatusAPICall($ip, $port, $secret);

	if (!array_key_exists("--json", $args["named"])) {
		if ($status["debug_active"]) {
			printf("*** DEBUGGING ACTIVE ***\n\n");
		}

		printf("Uptime                 : %5u s\n", $status["uptime"]);
		//printf("Upstream latency       : %5d ms\n", $status["upstream_latency"]);
		printf("\n");
		printf("DNS Queries total      : %5u\n", $status["incoming_queries"]);
		printf("DNS Queries served     : %5u\n", $status["completed_queries"]);
		printf("\n");
		printf("Ticks per second       : %5u T/s\n", $status["ticks_per_second"]);
		printf("\n");
		printf("Random bytes available : %5u bytes\n", $status["random_bytes_available"]);
	//	printf("\n");
	//	printf("Tracked metric         : %5u\n", $status["metric_type"]);
	//	printf("Tracked metric HEAD    : %5u\n", $status["metric_values"][0]);

		return;
	}

	echo json_encode($status, JSON_PRETTY_PRINT)."\n";
}

?>
