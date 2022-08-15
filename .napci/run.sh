#!/bin/bash -eux

rm -rf .napci/build_files
rm -rf .napci/upload_files

./ci/run.sh

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

rm .napci/build_files.tmp/ddns-arduino-cli.zip

# upload_files
cd .napci/upload_files.tmp/

# ln -s ...

cd ../../

mv .napci/upload_files.tmp .napci/upload_files
