ARG VARIANT=ubuntu-24.04
FROM mcr.microsoft.com/devcontainers/base:${VARIANT}
USER root

# Install needed packages. Use a separate RUN statement to add your own dependencies.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install software-properties-common build-essential cmake valgrind clang lldb llvm gdb \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Setup ENV vars for vcpkg
ENV VCPKG_ROOT=/usr/local/vcpkg \
    VCPKG_DOWNLOADS=/usr/local/vcpkg-downloads
ENV PATH="${PATH}:${VCPKG_ROOT}"

ARG USERNAME=vscode

# Install vcpkg itself: https://github.com/microsoft/vcpkg/blob/master/README.md#quick-start-unix
COPY install-vcpkg.sh /tmp/
RUN chmod +x /tmp/install-vcpkg.sh \
    && ./tmp/install-vcpkg.sh ${USERNAME} \
    && rm -f /tmp/install-vcpkg.sh

# [Optional] Uncomment this section to install additional OS packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends python3 python3-pip python3-venv \
    && apt-get -y install --no-install-recommends make ninja-build ccache \
    && apt-get -y install --no-install-recommends lcov
ARG GCC_VERSION
COPY install-gcc.sh /tmp/
RUN chmod +x /tmp/install-gcc.sh \
    && ./tmp/install-gcc.sh ${GCC_VERSION} \
    && rm -f /tmp/install-gcc.sh
ARG CLANG_VERSION
COPY install-clang.sh /tmp/
RUN chmod +x /tmp/install-clang.sh \
    && ./tmp/install-clang.sh ${CLANG_VERSION} \
    && rm -f /tmp/install-clang.sh
ARG CMAKE_VERSION
COPY install-cmake.sh /tmp/
RUN chmod +x /tmp/install-cmake.sh \
    && ./tmp/install-cmake.sh ${CMAKE_VERSION} \
    && rm -f /tmp/install-cmake.sh
ARG CPPCHECK_VERSION
COPY install-cppcheck.sh /tmp/
RUN chmod +x /tmp/install-cppcheck.sh \
    && ./tmp/install-cppcheck.sh ${CPPCHECK_VERSION} \
    && rm -f /tmp/install-cppcheck.sh

# Copy gdb config file (enables .gdbinit in project root)
COPY --chown=${USERNAME}:${USERNAME} user.gdbinit /home/${USERNAME}/.gdbinit
