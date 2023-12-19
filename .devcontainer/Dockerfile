ARG ZEPHYR_CONTAINER_VERSION="latest"
FROM ghcr.io/zephyrproject-rtos/ci:${ZEPHYR_CONTAINER_VERSION}

USER user

RUN pip install semver
RUN pip install git+https://github.com/antmicro/pyrenode.git
RUN pip install git+https://github.com/antmicro/dts2repl.git