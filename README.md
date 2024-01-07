# Zephyr Dynamic Linking using udynlink

This is a minimal Zephyr app that uses [udynlink](https://github.com/kinsamanka/udynlink) for dynamic linking on Cortex-M MCUs.

## Getting Started

Before getting started, make sure you have a proper Zephyr development
environment. Follow the official
[Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html).

Make sure the **Host Tools** are installed when setting up the [Zephyr SDK bundle](https://github.com/zephyrproject-rtos/sdk-ng/releases).

### Initialization

The first step is to initialize the workspace folder (``workspace``) where
the ``udynlink-app`` and all Zephyr modules will be cloned. Run the following
command:

```shell
# initialize workspace for the udynlink-app
west init -m https://github.com/kinsamanka/udynlink-app workspace

# update Zephyr modules
cd workspace
west update --narrow -o=--depth=1
```

### Building and running

To build and run the application using the qemu emulator, run the following commands:

```shell
# build
west build udynlink-app

# test
west build -t run
```

