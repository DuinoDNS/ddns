<?php

define("LIBNAPC_GIT_HASH", "df62e527ee8fa17818e839c938e7f6117aebead4");

$hash = hash("sha1", "libnapc:dev@".LIBNAPC_GIT_HASH);

echo "https://stash.nap-software.com/$hash/libnapc-arduino.zip\n";
