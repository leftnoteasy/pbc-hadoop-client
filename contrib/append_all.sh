#! /bin/bash

# This tool can extract all proto files in mrv2 folder, and remove java package declerations
# usage <program> path/to/mrv2-source-folder

if [ $# -eq 0 ] || [ $# -gt 1 ]; then
  echo "usage: <program> dirname"
  exit
fi

find $1 -name "*.proto" | grep -v "hdfs" | grep -v "mapreduce" | xargs cat | grep -v "option java" | grep -v "^import \""
