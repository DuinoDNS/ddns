<?php

function ddns__calcAPIVersion($api_version_str) {
	$api_version = 0;

	for ($i = 0; $i < 4; ++$i) {
		$byte = ord($api_version_str[3 - $i]);

		$api_version |= ($byte << ($i * 8));
	}

	return str_pad(
		dechex($api_version),
		8,
		"0",
		STR_PAD_LEFT
	);
}

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

	$response = substr($answer_body, 4);
	$api_version = ddns__calcAPIVersion(
		substr($answer_body, 0, 4)
	);

	fwrite(STDERR, "API-Version: $api_version\n");

	return [
		"message" => $response,
		"api_version" => $api_version,
		"request_identifier" => $answer_request_identifier
	];
}

?>
