FROM mcr.microsoft.com/devcontainers/base:debian
USER root

# install base packages
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install software-properties-common build-essential cmake valgrind clang lldb llvm gdb \
    && apt-get -y install --no-install-recommends python3 python3-pip python3-venv \
    && apt-get -y install --no-install-recommends make ninja-build ccache \
    && apt-get -y install --no-install-recommends lcov \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# install vcpkg
ENV VCPKG_ROOT=/usr/local/vcpkg
ENV VCPKG_DOWNLOADS=/usr/local/vcpkg-downloads
ENV PATH="${PATH}:${VCPKG_ROOT}"
COPY install-vcpkg.sh /tmp/
RUN chmod +x /tmp/install-vcpkg.sh && ./tmp/install-vcpkg.sh && rm -f /tmp/install-vcpkg.sh

# install gcc
ARG GCC_VERSION
COPY install-gcc.sh /tmp/
RUN chmod +x /tmp/install-gcc.sh \
    && ./tmp/install-gcc.sh ${GCC_VERSION} \
    && rm -f /tmp/install-gcc.sh

# install clang
ARG CLANG_VERSION
COPY install-clang.sh /tmp/
RUN chmod +x /tmp/install-clang.sh \
    && ./tmp/install-clang.sh ${CLANG_VERSION} \
    && rm -f /tmp/install-clang.sh

# install cmake
ARG CMAKE_VERSION
COPY install-cmake.sh /tmp/
RUN chmod +x /tmp/install-cmake.sh \
    && ./tmp/install-cmake.sh ${CMAKE_VERSION} \
    && rm -f /tmp/install-cmake.sh

# install cppcheck
ARG CPPCHECK_VERSION
COPY install-cppcheck.sh /tmp/
RUN chmod +x /tmp/install-cppcheck.sh \
    && ./tmp/install-cppcheck.sh ${CPPCHECK_VERSION} \
    && rm -f /tmp/install-cppcheck.sh

# add support for .gdbinit file in project root
COPY --chown=${USERNAME}:${USERNAME} user.gdbinit /home/${USERNAME}/.gdbinit
