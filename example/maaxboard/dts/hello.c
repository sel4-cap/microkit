/*
 * Copyright 2021, Breakaway Consulting Pty. Ltd.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include <stdint.h>
#include <microkit.h>
#include <printf.h>

#define STR2(x) #x
#define STR(x) STR2(x)

#define INCBIN_SECTION ".rodata"

// this aligns start address to 16 and terminates byte array with explict 0
// which is not really needed, feel free to change it to whatever you want/need
#define INCBIN(name, file) \
    __asm__(".section " INCBIN_SECTION "\n" \
            ".global incbin_" STR(name) "_start\n" \
            ".balign 16\n" \
            "incbin_" STR(name) "_start:\n" \
            ".incbin \"" file "\"\n" \
            \
            ".global incbin_" STR(name) "_end\n" \
            ".balign 1\n" \
            "incbin_" STR(name) "_end:\n" \
            ".byte 0\n" \
    ); \
    extern __attribute__((aligned(16))) const char incbin_ ## name ## _start[]; \
    extern                              const char incbin_ ## name ## _end[]

INCBIN(device_tree, "kernel/kernel.bin");

void
init(void)
{
    printf("start = %p\n", &incbin_device_tree_start);
    printf("end = %p\n", &incbin_device_tree_end);
    printf("size = %zu\n", (char*)&incbin_device_tree_end - (char*)&incbin_device_tree_start);
    printf("first byte = 0x%02hhx\n", incbin_device_tree_start[0]);
}

void
notified(microkit_channel ch)
{
}