#!/usr/bin/env bash

set -e

CLANG_VERSION=${1:-"none"}

if [ "${CLANG_VERSION}" = "none" ]; then
    echo "No Clang version specified, skipping Clang installation"
    exit 0
fi

echo "Installing Clang..."

export DEBIAN_FRONTEND=noninteractive

TMP_DIR=$(mktemp -d -t clang-XXXXXXXXXX)
cd "${TMP_DIR}"
wget https://apt.llvm.org/llvm.sh
chmod +x "${TMP_DIR}/llvm.sh"
source "${TMP_DIR}/llvm.sh" ${CLANG_VERSION} all

update-alternatives --install /usr/bin/llvm-config           llvm-config           /usr/bin/llvm-config-${CLANG_VERSION} 200       \
                    --slave   /usr/bin/llvm-ar               llvm-ar               /usr/bin/llvm-ar-${CLANG_VERSION}               \
                    --slave   /usr/bin/llvm-as               llvm-as               /usr/bin/llvm-as-${CLANG_VERSION}               \
                    --slave   /usr/bin/llvm-bcanalyzer       llvm-bcanalyzer       /usr/bin/llvm-bcanalyzer-${CLANG_VERSION}       \
                    --slave   /usr/bin/llvm-c-test           llvm-c-test           /usr/bin/llvm-c-test-${CLANG_VERSION}           \
                    --slave   /usr/bin/llvm-cat              llvm-cat              /usr/bin/llvm-cat-${CLANG_VERSION}              \
                    --slave   /usr/bin/llvm-cfi-verify       llvm-cfi-verify       /usr/bin/llvm-cfi-verify-${CLANG_VERSION}       \
                    --slave   /usr/bin/llvm-cov              llvm-cov              /usr/bin/llvm-cov-${CLANG_VERSION}              \
                    --slave   /usr/bin/llvm-cvtres           llvm-cvtres           /usr/bin/llvm-cvtres-${CLANG_VERSION}           \
                    --slave   /usr/bin/llvm-cxxdump          llvm-cxxdump          /usr/bin/llvm-cxxdump-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-cxxfilt          llvm-cxxfilt          /usr/bin/llvm-cxxfilt-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-diff             llvm-diff             /usr/bin/llvm-diff-${CLANG_VERSION}             \
                    --slave   /usr/bin/llvm-dis              llvm-dis              /usr/bin/llvm-dis-${CLANG_VERSION}              \
                    --slave   /usr/bin/llvm-dlltool          llvm-dlltool          /usr/bin/llvm-dlltool-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-dwarfdump        llvm-dwarfdump        /usr/bin/llvm-dwarfdump-${CLANG_VERSION}        \
                    --slave   /usr/bin/llvm-dwp              llvm-dwp              /usr/bin/llvm-dwp-${CLANG_VERSION}              \
                    --slave   /usr/bin/llvm-exegenis         llvm-exegenis         /usr/bin/llvm-exgenis-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-extract          llvm-extract          /usr/bin/llvm-extract-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-lib              llvm-lib              /usr/bin/llvm-lib-${CLANG_VERSION}              \
                    --slave   /usr/bin/llvm-link             llvm-link             /usr/bin/llvm-link-${CLANG_VERSION}             \
                    --slave   /usr/bin/llvm-lto              llvm-lto              /usr/bin/llvm-lto-${CLANG_VERSION}              \
                    --slave   /usr/bin/llvm-lto2             llvm-lto2             /usr/bin/llvm-lto2-${CLANG_VERSION}             \
                    --slave   /usr/bin/llvm-mc               llvm-mc               /usr/bin/llvm-mc-${CLANG_VERSION}               \
                    --slave   /usr/bin/llvm-mca              llvm-mca              /usr/bin/llvm-mca-${CLANG_VERSION}              \
                    --slave   /usr/bin/llvm-mcmarkup         llvm-mcmarkup         /usr/bin/llvm-mcmarkup-${CLANG_VERSION}         \
                    --slave   /usr/bin/llvm-modeextract      llvm-modeextract      /usr/bin/llvm-modeextract-${CLANG_VERSION}      \
                    --slave   /usr/bin/llvm-mt               llvm-mt               /usr/bin/llvm-mt-${CLANG_VERSION}               \
                    --slave   /usr/bin/llvm-nm               llvm-nm               /usr/bin/llvm-nm-${CLANG_VERSION}               \
                    --slave   /usr/bin/llvm-objcopy          llvm-objcopy          /usr/bin/llvm-objcopy-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-objdump          llvm-objdump          /usr/bin/llvm-objdump-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-opt-report       llvm-opt-report       /usr/bin/llvm-opt-report-${CLANG_VERSION}       \
                    --slave   /usr/bin/llvm-pdbutil          llvm-pdbutil          /usr/bin/llvm-pdbutil-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-ranlib           llvm-ranlib           /usr/bin/llvm-ranlib-${CLANG_VERSION}           \
                    --slave   /usr/bin/llvm-rc               llvm-rc               /usr/bin/llvm-rc-${CLANG_VERSION}               \
                    --slave   /usr/bin/llvm-readelf          llvm-readelf          /usr/bin/llvm-readelf-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-readobj          llvm-readobj          /usr/bin/llvm-readobj-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-rtdyld           llvm-rtdyld           /usr/bin/llvm-rtdyld-${CLANG_VERSION}           \
                    --slave   /usr/bin/llvm-size             llvm-size             /usr/bin/llvm-size-${CLANG_VERSION}             \
                    --slave   /usr/bin/llvm-split            llvm-split            /usr/bin/llvm-split-${CLANG_VERSION}            \
                    --slave   /usr/bin/llvm-stress           llvm-stress           /usr/bin/llvm-stress-${CLANG_VERSION}           \
                    --slave   /usr/bin/llvm-strings          llvm-strings          /usr/bin/llvm-strings-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-strip            llvm-strip            /usr/bin/llvm-strip-${CLANG_VERSION}            \
                    --slave   /usr/bin/llvm-symbolizer       llvm-symbolizer       /usr/bin/llvm-symbolizer-${CLANG_VERSION}       \
                    --slave   /usr/bin/llvm-tblgen           llvm-tblgen           /usr/bin/llvm-tblgen-${CLANG_VERSION}           \
                    --slave   /usr/bin/llvm-undname          llvm-undname          /usr/bin/llvm-undname-${CLANG_VERSION}          \
                    --slave   /usr/bin/llvm-xray             llvm-xray             /usr/bin/llvm-xray-${CLANG_VERSION}

update-alternatives --install /usr/bin/clang                 clang                 /usr/bin/clang-${CLANG_VERSION} 200             \
                    --slave   /usr/bin/clang++               clang++               /usr/bin/clang++-${CLANG_VERSION}               \
                    --slave   /usr/bin/clangd                clangd                /usr/bin/clangd-${CLANG_VERSION}                \
                    --slave   /usr/bin/clang-check           clang-check           /usr/bin/clang-check-${CLANG_VERSION}           \
                    --slave   /usr/bin/clang-cl              clang-cl              /usr/bin/clang-cl-${CLANG_VERSION}              \
                    --slave   /usr/bin/clang-cpp             clang-cpp             /usr/bin/clang-cpp-${CLANG_VERSION}             \
                    --slave   /usr/bin/clang-format          clang-format          /usr/bin/clang-format-${CLANG_VERSION}          \
                    --slave   /usr/bin/clang-format-diff     clang-format-diff     /usr/bin/clang-format-diff-${CLANG_VERSION}     \
                    --slave   /usr/bin/clang-import-test     clang-import-test     /usr/bin/clang-import-test-${CLANG_VERSION}     \
                    --slave   /usr/bin/clang-include-fixer   clang-include-fixer   /usr/bin/clang-include-fixer-${CLANG_VERSION}   \
                    --slave   /usr/bin/clang-offload-bundler clang-offload-bundler /usr/bin/clang-offload-bundler-${CLANG_VERSION} \
                    --slave   /usr/bin/clang-query           clang-query           /usr/bin/clang-query-${CLANG_VERSION}           \
                    --slave   /usr/bin/clang-rename          clang-rename          /usr/bin/clang-rename-${CLANG_VERSION}          \
                    --slave   /usr/bin/clang-reorder-fields  clang-reorder-fields  /usr/bin/clang-reorder-fields-${CLANG_VERSION}  \
                    --slave   /usr/bin/clang-tidy            clang-tidy            /usr/bin/clang-tidy-${CLANG_VERSION}            \
                    --slave   /usr/bin/asan_symbolize        asan_symbolize        /usr/bin/asan_symbolize-${CLANG_VERSION}        \
                    --slave   /usr/bin/bugpoint              bugpoint              /usr/bin/bugpoint-${CLANG_VERSION}              \
                    --slave   /usr/bin/c-index-test          c-index-test          /usr/bin/c-index-test-${CLANG_VERSION}          \
                    --slave   /usr/bin/dsymutil              dsymutil              /usr/bin/dsymutil-${CLANG_VERSION}              \
                    --slave   /usr/bin/lld                   lld                   /usr/bin/lld-${CLANG_VERSION}                   \
                    --slave   /usr/bin/llc                   llc                   /usr/bin/llc-${CLANG_VERSION}                   \
                    --slave   /usr/bin/lli                   lli                   /usr/bin/lli-${CLANG_VERSION}                   \
                    --slave   /usr/bin/ld.lld                ld.lld                /usr/bin/ld.lld-${CLANG_VERSION}                \
                    --slave   /usr/bin/lld-link              lld-link              /usr/bin/lld-link-${CLANG_VERSION}              \
                    --slave   /usr/bin/lldb                  lldb                  /usr/bin/lldb-${CLANG_VERSION}                  \
                    --slave   /usr/bin/lldb-server           lldb-server           /usr/bin/lldb-server-${CLANG_VERSION}           \
                    --slave   /usr/bin/obj2yaml              obj2yaml              /usr/bin/obj2yaml-${CLANG_VERSION}              \
                    --slave   /usr/bin/opt                   opt                   /usr/bin/opt-${CLANG_VERSION}                   \
                    --slave   /usr/bin/sanstats              sanstats              /usr/bin/sanstats-${CLANG_VERSION}              \
                    --slave   /usr/bin/verify-uselistorder   verify-uselistorder   /usr/bin/verify-uselistorder-${CLANG_VERSION}   \
                    --slave   /usr/bin/wasm-ld               wasm-ld               /usr/bin/wasm-ld-${CLANG_VERSION}               \
                    --slave   /usr/bin/yaml2obj              yaml2obj              /usr/bin/yaml2obj-${CLANG_VERSION}
