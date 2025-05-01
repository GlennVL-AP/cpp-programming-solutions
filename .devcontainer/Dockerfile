FROM mcr.microsoft.com/devcontainers/base:debian

USER root

# install base packages
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install software-properties-common build-essential cmake valgrind clang lldb llvm gdb \
    && apt-get -y install --no-install-recommends python3 python3-pip python3-venv \
    && apt-get -y install --no-install-recommends make ninja-build ccache \
    && apt-get -y install --no-install-recommends lcov \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# install vcpkg, clang, cmake, cppcheck
ARG CLANG_VERSION
ARG CMAKE_VERSION
ARG CPPCHECK_VERSION
ENV VCPKG_ROOT=/usr/local/vcpkg
ENV VCPKG_DOWNLOADS=/usr/local/vcpkg-downloads
COPY install-*.sh /tmp/
RUN chmod +x /tmp/install-*.sh \
 && ./tmp/install-vcpkg.sh \
 && ./tmp/install-clang.sh ${CLANG_VERSION} \
 && ./tmp/install-cmake.sh ${CMAKE_VERSION} \
 && ./tmp/install-cppcheck.sh ${CPPCHECK_VERSION} \
 && rm -f /tmp/install-*.sh

# add support for .lldbinit files in project root
COPY --chown=vscode:vscode user.lldbinit /home/vscode/.lldbinit

USER vscode
