#!/bin/bash -eufx

php build.scripts/dynamic-files.php

rm -rf arduino.tmp
mkdir arduino.tmp

mkdir -p dist

cp -r src arduino.tmp/src
cp library.properties arduino.tmp

cd arduino.tmp

zip -r ../arduino.tmp.zip .

cd ..

mv arduino.tmp.zip dist/arduino.zip

rm -rf arduino.tmp
