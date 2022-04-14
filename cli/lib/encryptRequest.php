<?php

function ddns__encryptRequest($request, $secret) {
	$key = hash("sha256", $secret, true);
	$iv = openssl_random_pseudo_bytes(16);
	$request_identifier = openssl_random_pseudo_bytes(16);

	$message        = "ddns_".$request_identifier.$request;
	$padded_message = $message.str_repeat("\x00", 976 - strlen($message));

	$ciphermessage = openssl_encrypt(
		$padded_message, "aes-256-cbc", $key,
		OPENSSL_RAW_DATA | OPENSSL_ZERO_PADDING,
		$iv
	);

	$hmac = ddns__calculateHMACSHA256($ciphermessage, $secret);

	return [
		"message" => $hmac.$iv.$ciphermessage,
		"request_identifier" => $request_identifier
	];
}

?>
