<?php

function handleGetQHistory($ip, $port, $secret, $wants_json) {
	$qhistory = ddns__getQueryHistoryAPICall($ip, $port, $secret);

	var_dump($qhistory);

	return;

	if (!$wants_json) {
		printf("Uptime                 : %5u s\n", $status["uptime"]);
		printf("Upstream latency       : %5d ms\n", $status["upstream_latency"]);
		printf("\n");
		printf("DNS Queries total      : %5u\n", $status["dns_queries"]["total"]);
		printf("DNS Queries served     : %5u\n", $status["dns_queries"]["served"]);
		printf("DNS Queries timeout    : %5u\n", $status["dns_queries"]["timeout"]);
		printf("DNS Queries invalid    : %5u\n", $status["dns_queries"]["invalid"]);
		printf("DNS Queries throughput : %5u\n", $status["dns_queries"]["throughput"]);
		printf("\n");
		printf("TPS                    : %5u\n", $status["ticks_per_second"]);
		printf("\n");
		printf("Random bytes available : %5u\n", $status["random_bytes_available"]);
		printf("\n");
		printf("Tracked metric         : %5u\n", $status["metric_type"]);
		printf("Tracked metric HEAD    : %5u\n", $status["metric_values"][0]);

		return;
	}

	echo json_encode($status, JSON_PRETTY_PRINT)."\n";
}

?>
