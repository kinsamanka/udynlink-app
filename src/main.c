/*
 * Copyright (c) 2024 GP Orcullo
 * SPDX-License-Identifier: Apache-2.0
 */

#include <udynlink/udynlink.h>

#include <stdlib.h>
#include <string.h>
#include <zephyr/kernel.h>

__aligned(4)
#include "hello_world_module_data.h"

__aligned(4)
#include "hello_world_cpp_module_data.h"

uint32_t udynlink_external_resolve_symbol(const char *name) {
    if (!strcmp(name, "printf"))
        return (uint32_t)&printf;
    else
        return 0;
}

void udynlink_external_free(void *p) {
    free(p);
}

void *udynlink_external_malloc(size_t size) {
    return malloc(size);
}

void udynlink_external_vprintf(const char *s, va_list va) {
    vprintf(s, va);
}

int main(void) {
    udynlink_module_t mod;

    printk("\nZephyr udynlink Example Application\n\n");

    udynlink_set_debug_level(UDYNLINK_DEBUG_WARNING);

    if (!udynlink_load_module(&mod, hello_world_module_data, NULL, 0,
                              UDYNLINK_LOAD_MODE_XIP)) {
        udynlink_sym_t sym;

        if (udynlink_lookup_symbol(&mod, "test", &sym) != NULL) {

            /* load LOT address to R9 */
            register void * const mod_base __asm__("r9") = mod.p_ram;
            __asm__ volatile("\n\t" ::"r"(mod_base));

            printk("Running test1:\n");
            int (*p_func)(void) = (int (*)(void))sym.val;
            printk("Result %d\n\n", p_func());
        }
    }

    if (!udynlink_load_module(&mod, hello_world_cpp_module_data, NULL, 0,
                              UDYNLINK_LOAD_MODE_XIP)) {
        udynlink_sym_t sym;

        /* load LOT address to R9 */
        register void * const mod_base __asm__("r9") = mod.p_ram;
        __asm__ volatile("\n\t" ::"r"(mod_base));

        if (udynlink_lookup_symbol(&mod, "test2", &sym) != NULL) {
            printk("Running test2:\n");
            int (*p_func)(void) = (int (*)(void))sym.val;
            printk("Result %d\n\n", p_func());
        }

        if (udynlink_lookup_symbol(&mod, "test3", &sym) != NULL) {
            printk("Running test3:\n");
            int (*p_func)(int, int, int) = (int (*)(int, int, int))sym.val;
            printk("Result %d\n\n", p_func(1, 2, 3));
        }
    }
    return 0;
}
