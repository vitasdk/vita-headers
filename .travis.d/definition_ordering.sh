#!/usr/bin/env bash
set -e
DB_FILE_PATH='./db.yml'
LIBSEP="        functions:" # name of the yaml block we want to check
IFS=@
# iterate over each block and `sort --check` they content
for lib in $(grep "$LIBSEP\|          " "$DB_FILE_PATH" | sed "s/$LIBSEP/$IFS/"); do
  printf "$lib" | grep -o "          [^:]*"| LC_ALL=C sort -c
done