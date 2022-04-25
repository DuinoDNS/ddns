<?php

function handleRestart($ip, $port, $secret, $args) {
	echo ddns__restartAPICall($ip, $port, $secret);
}

?>
