#!/bin/bash -eufx

./build.scripts/build.php

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

mv ArduinoSketch/build/arduino.samd.mkrwifi1010/ArduinoSketch.ino.bin \
	dist/arduino.samd.mkrwifi1010.bin

rm -rf ArduinoSketch/build
