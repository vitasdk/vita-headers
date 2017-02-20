#!/usr/bin/env bash
set -e
cd $TRAVIS_BUILD_DIR
curl -sL https://github.com/vitasdk/autobuilds/releases | grep linux | grep tar.bz2 | head -n 1 | cut -d '"' -f 2 | xargs -I PATH curl -L https://github.comPATH | tar xj
