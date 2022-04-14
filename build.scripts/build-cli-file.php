<?php

chdir(__DIR__."/../cli");

echo '#!/usr/bin/env php'.PHP_EOL;

function process_src_dir($dir) {
	$entries = scandir($dir);

	foreach ($entries as $entry) {
		if (substr($entry, 0, 1) === ".") continue;
		if (!is_file("$dir/$entry")) continue;

		echo file_get_contents("$dir/$entry");
	}
}

process_src_dir("lib");
process_src_dir("call");
process_src_dir("cmd");

echo file_get_contents("index.php");
