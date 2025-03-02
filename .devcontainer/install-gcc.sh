#!/usr/bin/env bash

set -e

GCC_VERSION=${1:-"none"}

if [ "${GCC_VERSION}" = "none" ]; then
    echo "No GCC version specified, skipping GCC installation"
    exit 0
fi

echo "Installing GCC..."

export DEBIAN_FRONTEND=noninteractive

add-apt-repository -y ppa:ubuntu-toolchain-r/test
apt-get update
apt-get -y install gcc-${GCC_VERSION} g++-${GCC_VERSION}

update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-${GCC_VERSION} 200 \
                    --slave /usr/bin/g++ g++ /usr/bin/g++-${GCC_VERSION} \
                    --slave /usr/bin/gcov gcov /usr/bin/gcov-${GCC_VERSION}
