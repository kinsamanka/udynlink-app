# Copyright (c) 2024 GP Orcullo
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20)

set(BOARD qemu_cortex_m3)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(udynlink-app)

set(UDYNLINK_SCRIPT_DIR "${UDYNLINK_SOURCE_DIR}/../scripts")
set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)

add_subdirectory(hello_world)
add_subdirectory(hello_world_cpp)

target_compile_definitions(app PRIVATE UDYNLINK_SKIP_PROLOGUE)
target_sources(app PRIVATE src/main.c)

add_dependencies(app hello_world hello_world_cpp)
