<?php

function ddns__decryptAnswer($answer, $secret) {
	$key             = hash("sha256", $secret, true);
	$hmac            = substr($answer, 0, 32);
	$iv              = substr($answer, 32, 16);
	$ciphermessage   = substr($answer, 16 + 32);

	$calculated_hmac = ddns__calculateHMACSHA256($ciphermessage, $secret);

	if (!ddns__compareHMACSHA256($calculated_hmac, $hmac)) {
		throw new Error("Invalid HMAC in response.");
	}

	$plaintext = openssl_decrypt(
		$ciphermessage, "aes-256-cbc", $key, OPENSSL_RAW_DATA | OPENSSL_ZERO_PADDING,
		$iv
	);

	if (substr($plaintext, 16, strlen("ddns_")) !== "ddns_") {
		throw new Error("Response should start with 'ddns_'!");
	}

	$answer_request_identifier = substr($plaintext, 0, 16);

	$answer_body = substr($plaintext, strlen("ddns_") + 16);

	return [
		"message" => $answer_body,
		"request_identifier" => $answer_request_identifier
	];
}

?>
