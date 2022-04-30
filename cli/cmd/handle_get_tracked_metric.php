<?php

function handleGetTrackedMetric($ip, $port, $secret, $args) {
	$tracked_metric = ddns__getTrackedMetricAPICall($ip, $port, $secret);

	if (!array_key_exists("--json", $args["named"])) {

		echo "Kind: ".$tracked_metric["kind"]."\n";

		foreach ($tracked_metric["values"] as $i => $value) {
			if ($value === -1) continue;

			printf("[%4d] value=%d\n", $i, $value);
		}

		return;
	}

	echo json_encode($tracked_metric, JSON_PRETTY_PRINT)."\n";
}

?>
