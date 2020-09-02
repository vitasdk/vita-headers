#!/usr/bin/env bash
set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

ARCHIVE_DIR="${HOME}/downloads"

DOXYGEN_VERSION="1.8.20"
DOXYGEN_BIN="doxygen-${DOXYGEN_VERSION}.linux.bin.tar.gz"
DOXYGEN_BIN_SHA256SUM="502f78155b30374eb674bac28f73384f1976ec0fd41cf4fc17ef24d30c1669f0"

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
