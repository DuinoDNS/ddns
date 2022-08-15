#!/usr/bin/env php
<?php

$project_root = realpath(__DIR__."/../");

$template = "library:
  enable_unsafe_install: true
directories:
  data: $project_root/.napci/tmp/arduino-cli-data
  downloads: $project_root/.napci/tmp/arduino-cli-staging
  user: $project_root/.napci/tmp/arduino-cli-sketchbook
";

file_put_contents("$project_root/.napci/tmp/arduino-cli-config.yaml", $template);
