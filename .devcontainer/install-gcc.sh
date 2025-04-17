#!/usr/bin/env bash

set -e

GCC_VERSION=${1:-"none"}

if [ "${GCC_VERSION}" = "none" ]; then
    echo "No GCC version specified, skipping GCC installation"
    exit 0
fi

apt_get_update_if_needed() {
    if [ ! -d "/var/lib/apt/lists" ] || [ "$(ls /var/lib/apt/lists/ | wc -l)" = "0" ]; then
        echo "Running apt-get update..."
        apt-get update
    else
        echo "Skipping apt-get update."
    fi
}

check_packages() {
    if ! dpkg -s "$@" > /dev/null 2>&1; then
        apt_get_update_if_needed
        apt-get -y install --no-install-recommends "$@"
    fi
}

echo "Installing GCC..."

export DEBIAN_FRONTEND=noninteractive
check_packages build-essential python3 flex binutils perl libgmp-dev libmpfr-dev libmpc-dev libisl-dev texinfo bison

TMP_DIR=$(mktemp -d -t gcc-XXXXXXXXXX)
cd "${TMP_DIR}"
git clone --depth 1 --branch releases/gcc-${GCC_VERSION} git://gcc.gnu.org/git/gcc.git
cd gcc
./contrib/download_prerequisites
cd .. && mkdir objdir && cd objdir
$PWD/../gcc/configure --prefix=/opt/gcc-${GCC_VERSION} --disable-multilib --enable-languages=c,c++,lto
make -j$(nproc)
make install

update-alternatives --install /usr/bin/gcc gcc /opt/gcc-${GCC_VERSION}/bin/gcc 200 \
                    --slave /usr/bin/g++ g++ /opt/gcc-${GCC_VERSION}/bin/g++ \
                    --slave /usr/bin/gcov gcov /opt/gcc-${GCC_VERSION}/bin/gcov
