ARG ZEPHYR_CONTAINER_VERSION="latest"
FROM ghcr.io/zephyrproject-rtos/ci:${ZEPHYR_CONTAINER_VERSION}

USER user

RUN pip install semver
RUN pip install 'pyrenode3[all] @ git+https://github.com/antmicro/pyrenode3.git'
# RUN echo 'alias PYRENODE_ARCH_PKG="/usr/bin/renode"' >> ~/.bashrc
RUN echo 'alias PYRENODE_ARCH_PKG="https://builds.renode.io/renode-latest.pkg.tar.xz"' >> ~/.bashrc

RUN pip install git+https://github.com/antmicro/dts2repl.git