<?php

function handleClearDebug($ip, $port, $secret, $args) {
	echo ddns__setDebugAPICall($ip, $port, $secret, false);
}

?>
