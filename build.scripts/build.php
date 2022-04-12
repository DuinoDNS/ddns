#!/usr/bin/env php
<?php

chdir(__DIR__."/../");

system("./build.scripts/_build.sh", $code);

exit($code);
