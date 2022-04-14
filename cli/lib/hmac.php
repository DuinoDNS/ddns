<?php

function ddns__calculateHMACSHA256($message, $secret) {
	return hash_hmac("sha256", $message, hash("sha256", $secret), true);
}

function ddns__compareHMACSHA256($h1, $h2) {
	for ($i = 0; $i < 32; ++$i) {
		if ($h1[$i] !== $h2[$i]) return false;
	}

	return true;
}

?>
