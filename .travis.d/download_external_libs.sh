#!/usr/bin/env bash
set -e
curl -sL https://github.com/vitasdk/vdpm/raw/master/vdpm -o vdpm
chmod +x vdpm
curl -L https://github.com/vitasdk/vdpm/raw/master/include/install-packages.sh -o install-packages.sh
sed -i "s/\.\.\///" install-packages.sh
curl -L https://github.com/vitasdk/vdpm/raw/master/install-all.sh | sed -e "s/include\///" | bash > /dev/null
rm vdpm
