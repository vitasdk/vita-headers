#!/usr/bin/env bash
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

ARCHIVE_DIR="${HOME}/downloads"

DOXYGEN_VERSION="1.8.18"
DOXYGEN_BIN="doxygen-${DOXYGEN_VERSION}.linux.bin.tar.gz"
DOXYGEN_BIN_SHA256SUM="d589d17c1a5eec7586904a6df4bcdba585ed8e2a0c6afc825bb77e5cb17c275f"

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

download_and_unpack http://doxygen.nl/files/${DOXYGEN_BIN} \
    ${DOXYGEN_BIN} \
    ${DOXYGEN_BIN_SHA256SUM} \
    ${HOME}/doxygen
