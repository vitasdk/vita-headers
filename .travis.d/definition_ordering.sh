#!/usr/bin/env bash
set -e
DB_FILE_PATH='./db.yml'
LIBSEP="        \(functions\|variables\):" # name of the yaml block we want to check
IFS=@
dir='./db/'
for file in $dir; do
  echo $file

  # iterate over each block and `sort --check` they content
  for lib in $(grep "$LIBSEP\|          " "$file" | sed "s/$LIBSEP/$IFS/"); do
    printf "$lib" | grep -o "          [^:]*"| LC_ALL=C sort -c
  done
done

