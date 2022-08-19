#!/bin/bash -eufx

./build.scripts/build.php

#
# compile
#
LIBNAPC_ARDUINO_URL="$(php -f ./ci/get-libnapc-zip-url.php)"

curl "$LIBNAPC_ARDUINO_URL" > ./.napci/tmp/libnapc-arduino.zip

mkdir -p ./.napci/tmp/libnapc-arduino/libnapc

unzip ./.napci/tmp/libnapc-arduino.zip -d ./.napci/tmp/libnapc-arduino/libnapc/

cd ./.napci/tmp/libnapc-arduino && zip -r ../libnapc-arduino-cli.zip . && cd ../../../

/usr/local/bin/arduino-cli core install arduino:samd --config-file ./.napci/tmp/arduino-cli-config.yaml
/usr/local/bin/arduino-cli lib install Ethernet --config-file ./.napci/tmp/arduino-cli-config.yaml
/usr/local/bin/arduino-cli lib install SD --config-file ./.napci/tmp/arduino-cli-config.yaml
/usr/local/bin/arduino-cli lib install --zip-path ./.napci/tmp/libnapc-arduino-cli.zip --config-file ./.napci/tmp/arduino-cli-config.yaml
/usr/local/bin/arduino-cli lib install --zip-path ./dist/ddns-arduino-cli.zip --config-file ./.napci/tmp/arduino-cli-config.yaml

/usr/local/bin/arduino-cli compile --fqbn arduino:samd:mkrwifi1010 ./ArduinoSketch --config-file ./.napci/tmp/arduino-cli-config.yaml --export-binaries

mv ArduinoSketch/build/arduino.samd.mkrwifi1010/ArduinoSketch.ino.bin \
	dist/arduino.samd.mkrwifi1010.bin

rm -rf ArduinoSketch/build
