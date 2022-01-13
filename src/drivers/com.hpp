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

class Com 
{
private:
    uint16_t port;
public:
    Com(uint16_t port);
    void write(char const *s);
    void putc(char c);
};