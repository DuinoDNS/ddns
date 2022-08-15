#!/bin/bash -eufx

#
# clear folders
#
rm -rf .napci/build_files
rm -rf .napci/build_files.tmp

rm -rf .napci/upload_files
rm -rf .napci/upload_files.tmp

rm -rf .napci/tmp


mkdir .napci/build_files.tmp
mkdir .napci/upload_files.tmp
mkdir .napci/tmp

#
# create arduino config on the fly
# because paths need to be absolute and be known
#
./ci/prepare-arduino-config-file.php > ./.napci/tmp/arduino-cli-config.yaml
