#!/usr/bin/env php
<?php

require_once __DIR__."/x-php-utils/load.php";

function getReleaseVersion() {
	$git_branch = XPHPUtils::git_getCurrentBranch();
	$git_HEAD = XPHPUtils::git_getHEADHash();

	$release_version = $git_branch."-".substr($git_HEAD, 0, 7);

	if ($git_branch === "main") {
		$tmp = trim(exec("git describe --tags"));

		if (substr($tmp, 0, 1) === "v") {
			$release_version = substr($tmp, 1);
		}
	}

	return $release_version;
}

chdir(__DIR__);

$url = getenv("DDNS_DEPLOY_URL");

$post = [
	"DDNS_DEPLOY_KEY"      => getenv("DDNS_DEPLOY_KEY"),
	"DDNS_GIT_BRANCH"      => XPHPUtils::git_getCurrentBranch(),
	"DDNS_GIT_HEAD"        => XPHPUtils::git_getHEADHash(),
	"DDNS_RELEASE_VERSION" => getReleaseVersion()
];

foreach ([
	"ddns-arduino.zip"
] as $file) {
	$post_key = str_replace(".", "_", $file);

	$file_path = __DIR__."/dist/$file";

	$post[$post_key] = curl_file_create($file_path);

	$post[$post_key."_sha256"] = hash_file("sha256", $file_path);
}

$ch = curl_init();

curl_setopt($ch, CURLOPT_URL, $url);
curl_setopt($ch, CURLOPT_POST, 1);
curl_setopt($ch, CURLOPT_POSTFIELDS, $post);

curl_setopt($ch, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);

$resp = curl_exec($ch);

$response_code = (int)curl_getinfo($ch, CURLINFO_HTTP_CODE);

$error_msg = "";

if (curl_errno($ch)) {
	$error_msg = curl_error($ch);
}

curl_close($ch);

if (strlen($error_msg)) {
	fwrite(STDERR, "curl error: $error_msg\n");
	exit(1);
} else if ($response_code !== 200) {
	fwrite(STDERR, "Error\n");
	exit(1);
}
