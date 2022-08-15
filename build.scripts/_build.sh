#!/bin/bash -eufx

php build.scripts/dynamic-files.php

rm -rf arduino.tmp
mkdir arduino.tmp

mkdir -p dist

php build.scripts/build-cli-file.php > dist/cli.php

cp -r src arduino.tmp/src
cp library.properties arduino.tmp

cd arduino.tmp

zip -r ../arduino.tmp.zip .

cd ..

mv arduino.tmp.zip dist/ddns-arduino.zip

cd arduino.tmp

mkdir ddns-nightly

mv src ddns-nightly
mv library.properties ddns-nightly

rm -f ../dist/ddns-arduino-cli.zip

ls -la ../dist

zip -r ../dist/ddns-arduino-cli.zip .

cd ..

rm -rf arduino.tmp
