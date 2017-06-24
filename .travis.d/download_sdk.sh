#!/usr/bin/env bash
set -e
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

cd $TRAVIS_BUILD_DIR
curl -sL $(python $DIR/last_built_toolchain.py) | tar xj
