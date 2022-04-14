<?php

function handleSetDebug($ip, $port, $secret, $wants_json) {
	$input = trim(fgets(STDIN));

	echo ddns__setDebugAPICall($ip, $port, $secret, $input === "set");
}

?>
