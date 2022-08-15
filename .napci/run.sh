#!/bin/bash -eux

./.napci/pre.sh
./ci/run.sh
./.napci/post.sh

#
# place files into correct directory
#

# build_files
mv dist/* .napci/build_files.tmp
rm .napci/build_files.tmp/ddns-arduino-cli.zip

mv .napci/build_files.tmp .napci/build_files

# upload_files
cd .napci/upload_files.tmp/

ln -s ../build_files/arduino.samd.mkrwifi1010.bin .

cd ../../

mv .napci/upload_files.tmp .napci/upload_files
