#!/bin/bash -eux

rm -rf .napci/build_files
rm -rf .napci/upload_files

./build.scripts/build.php
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

#
# place files into correct directory
#
rm -rf .napci/build_files.tmp
mkdir .napci/build_files.tmp
rm -rf .napci/upload_files.tmp
mkdir .napci/upload_files.tmp

# build_files
mv dist/* .napci/build_files.tmp
mv .napci/build_files.tmp .napci/build_files

# upload_files
cd .napci/upload_files.tmp/


cd ../../

mv .napci/upload_files.tmp .napci/upload_files
