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

db_build db.yml
db_build db_devkit.yml
