// Copyright (C) 2022 keyboard-slayer
// 
// This file is part of navy-cpp.
// 
// navy-cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// navy-cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with navy-cpp.  If not, see <http://www.gnu.org/licenses/>.

#include <stdint.h>
#include <stivale/stivale2.h>

#include "kernel/lib/const.hpp"
#include "drivers/com.hpp"

void _start(struct stivale2_header *stivale_hdr);

static uint8_t stack[KERNEL_STACK_SIZE];
static struct stivale2_header_tag_framebuffer fb_hdr_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = 0
    },

    .framebuffer_width  = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp    = 0
};

[[gnu::section(".stivale2hdr"), gnu::used]] static struct stivale2_header stivale_hdr = {
    .entry_point = (uintptr_t) _start,
    .stack = (uintptr_t) stack + sizeof(stack),
    .flags = (1 << 1),
    .tags = (uintptr_t) &fb_hdr_tag,
};

void _start([[maybe_unused]] struct stivale2_header *stivale_hdr)
{
    Com out(0x3F8);
    out.write("Hello World !\n");
    for (;;);
}