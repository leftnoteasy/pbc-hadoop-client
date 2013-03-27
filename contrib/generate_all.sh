#! /bin/bash

# This tool can extract all proto files in mrv2 folder, and generate file
# descriptor for all .proto file, this will be used by hadoop-c-client
# usage <program> path/to/mrv2-source-folder/ generate_dir/

if [ $# -eq 0 ] || [ $# -gt 2 ]; then
  echo "usage: <program> dirname generate_dir"
  echo "example: generate_all download/hadoop-2.0.2/ pb/hadoop-2.0.2"
  exit
fi

mkdir $2

files=`find $1 -name "*.proto"`;

for file in $files
do
   cp $file $2
done

copied_files=`ls $2`

for file in $copied_files
do
   protoc -I$2/ -o$2/$file.pb $2/$file
done
