#!/bin/bash -eux

rm -rf .napci/build_files
rm -rf .napci/upload_files

./build.scripts/build.php

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
