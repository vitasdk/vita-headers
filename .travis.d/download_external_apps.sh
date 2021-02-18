#!/usr/bin/env bash
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

ARCHIVE_DIR="${HOME}/downloads"

DOXYGEN_VERSION="1.9.1"
DOXYGEN_BIN="doxygen-${DOXYGEN_VERSION}.linux.bin.tar.gz"
DOXYGEN_BIN_SHA256SUM="8aa8da80baca22aa98fb05ed86e3ed7be7821ffd8073fc7dbc9b0ed2606e2825"

# in this time, only support tgz
function download_and_unpack {
    local url=$1
    local filename="${ARCHIVE_DIR}/$2"
    local hashsum="$3  ${filename}"
    local dest_dir=$4

    mkdir -p ${dest_dir}
    cd ${dest_dir}

    if [ ! -f ${filename} ];then
        curl -Lo ${filename} ${url}
    fi

    if ! echo ${hashsum} | sha256sum -c ; then
        cd ${DIR}
        rm -rf ${dest_dir} ${filename}
        return 1
    fi

    tar xzf ${filename}
    return 0
}

mkdir -p ${ARCHIVE_DIR}

download_and_unpack https://www.doxygen.nl/files/${DOXYGEN_BIN} \
    ${DOXYGEN_BIN} \
    ${DOXYGEN_BIN_SHA256SUM} \
    ${HOME}/doxygen
