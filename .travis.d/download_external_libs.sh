#!/usr/bin/env bash
set -e
curl -sL https://github.com/vitasdk/vdpm/raw/master/vdpm -o vdpm
chmod +x vdpm
curl -L https://github.com/vitasdk/vdpm/raw/master/install-all.sh | bash > /dev/null
rm vdpm
