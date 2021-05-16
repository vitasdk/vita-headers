#!/usr/bin/env bash

function db_build {
    local db_file=$1

    cd $TRAVIS_BUILD_DIR
    cp -r include/* $VITASDK/arm-vita-eabi/include
    vita-libs-gen ${db_file} output
    cd output
    make > /dev/null
    cp *_stub.a $VITASDK/arm-vita-eabi/lib

    return 0
}

dir='./db/*'
for file in $dir; do
  echo $file
  db_build $file
done
