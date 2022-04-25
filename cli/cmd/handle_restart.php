<?php

function handleRestart($ip, $port, $secret) {
	echo ddns__restartAPICall($ip, $port, $secret);
}

?>
