#!/usr/bin/env bash

set -e

CPPCHECK_VERSION=${1:-"none"}

if [ "${CPPCHECK_VERSION}" = "none" ]; then
    echo "No CppCheck version specified, skipping CppCheck installation"
    exit 0
fi

cleanup() {
    EXIT_CODE=$?
    set +e
    if [[ -n "${TMP_DIR}" ]]; then
        echo "Executing cleanup of tmp files"
        rm -Rf "${TMP_DIR}"
    fi
    exit $EXIT_CODE
}
trap cleanup EXIT

echo "Installing CppCheck..."

TMP_DIR=$(mktemp -d -t cppcheck-XXXXXXXXXX)
cd "${TMP_DIR}"
git clone --depth 1 --branch ${CPPCHECK_VERSION} https://github.com/danmar/cppcheck.git
cd cppcheck
mkdir build && cd build
cmake -G "Unix Makefiles" -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
make
make install
