<?php

function systemOrDie($cmd) {
	system($cmd, $code);

	if ($code !== 0) exit($code);
}

systemOrDie("php build.scripts/create-api-calls-files.php");
systemOrDie("php build.scripts/create-config-dump.php");
systemOrDie("php build.scripts/create-config-handle-key-value.php");
systemOrDie("php build.scripts/create-config-write.php");
