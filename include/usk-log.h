/*
    usk-project
    Copyright (C) 2018  Giovanni Davide Vergine

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INCLUDE_USK_LOG_H_
#define INCLUDE_USK_LOG_H_

#include <stdint.h>

#define LOG_DEBUG 0x01
#define LOG_INFO  0x02
#define LOG_WARN  0x04
#define LOG_ERROR 0x08

//syscalls
void set_usk_log_level(uint8_t level);
void usk_log(uint8_t level, const char* format, ...);



#endif /* INCLUDE_USK_LOG_H_ */
