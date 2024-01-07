# Copyright (c) 2024 GP Orcullo
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(hello_world_cpp)

add_executable(
    ${PROJECT_NAME}
    hello_world.cpp
    ${UDYNLINK_SCRIPT_DIR}/cpp_init_fini.c
    )

set_target_properties(
    ${PROJECT_NAME} 
    PROPERTIES
        OUTPUT_NAME "hello_world_cpp.elf"
    )

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
        "-fPIE"
        "-msingle-pic-base"
        "-mpic-register=r9"
        "-fomit-frame-pointer"
        "-mno-pic-data-is-text-relative"
        "-mlong-calls"
        "-mthumb"
        $<$<COMPILE_LANGUAGE:C>:-x c>
        $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit -fno-exceptions -fno-rtti>
    )

target_link_options(
    ${PROJECT_NAME} 
    PRIVATE
        "-nostartfiles"
        "-nodefaultlibs"
        "-nostdlib"
        "-Wl,--unresolved-symbols=ignore-in-object-files"
        "-Wl,--emit-relocs"
        "-Wl,-e,0"
        "-T;${UDYNLINK_SCRIPT_DIR}/code_before_data.ld"
    )

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
        ${_Python3_EXECUTABLE} ${UDYNLINK_SCRIPT_DIR}/mkmodule
            $<TARGET_FILE:${PROJECT_NAME}>
            --gen-c-header --no-debug
            --header-path ${gen_dir}
            --bin-name ${gen_dir}${PROJECT_NAME}.bin
    COMMENT "This generates the loadable image"
    VERBATIM
)
