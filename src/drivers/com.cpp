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

#include "com.hpp"
#include "kernel/lib/asm.hpp"

Com::Com(uint16_t port)
{
    this->port = port;

    asm_out8(port + 1, 0x00);
    asm_out8(port + 0, 0x03);
    asm_out8(port + 1, 0x00);
    asm_out8(port + 3, 0x03);
    asm_out8(port + 2, 0xc7);
    asm_out8(port + 4, 0x0b);
    asm_out8(port + 4, 0x1e);
    asm_out8(port + 0, 0xae);
    asm_out8(port + 4, 0x0f);
}

void Com::write(const char *s)
{
    while (*s)
    {
        this->putc(*s++);
    }
}

void Com::putc(char c)
{
    while ((asm_in8(this->port + 5) & 0x20) == 0);
    asm_out8(this->port, c);
}