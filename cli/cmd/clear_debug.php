<?php

function handleClearDebug($ip, $port, $secret, $wants_json) {
	echo ddns__setDebugAPICall($ip, $port, $secret, false);
}

?>
