/*
 * Copyright 2021, Breakaway Consulting Pty. Ltd.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
.extern main

.section ".text.start"

.global _start;
.type _start, %function;
_start:
    ldr x1, =_stack + 0xFFFE
    mov sp, x1
    b main
