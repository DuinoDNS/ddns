<?php

function handleSetDebug($ip, $port, $secret, $args) {
	echo ddns__setDebugAPICall($ip, $port, $secret, true);
}

?>
