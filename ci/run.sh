#!/bin/bash -eufx

./build.scripts/build.php
#
# create arduino config on the fly
# because paths need to be absolute and be known
#
./ci/prepare-arduino-config-file.php

#
# compile
#
/usr/local/bin/arduino-cli core install arduino:samd --config-file ./.napci/tmp/arduino-cli-config.yaml
/usr/local/bin/arduino-cli lib install Ethernet --config-file ./.napci/tmp/arduino-cli-config.yaml
/usr/local/bin/arduino-cli lib install SD --config-file ./.napci/tmp/arduino-cli-config.yaml
/usr/local/bin/arduino-cli lib install --git-url https://github.com/nap-software/libnapc-arduino-nightly-releases.git --config-file ./.napci/tmp/arduino-cli-config.yaml
unzip -l ./dist/ddns-arduino.zip
/usr/local/bin/arduino-cli lib install --verbose --zip-path ./dist/ddns-arduino-cli.zip --config-file ./.napci/tmp/arduino-cli-config.yaml

/usr/local/bin/arduino-cli compile --fqbn arduino:samd:mkrwifi1010 ./ArduinoSketch --config-file ./.napci/tmp/arduino-cli-config.yaml --export-binaries

mv ArduinoSketch/build/arduino.samd.mkrwifi1010/ArduinoSketch.ino.with_bootloader.hex \
	dist/arduino.samd.mkrwifi1010.hex

rm -rf ArduinoSketch/build
