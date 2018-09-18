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

#include <stdarg.h>
#include "usk-log.h"
#include <time.h>
#include <stdio.h>

static volatile uint8_t log_level;

void set_usk_log_level(uint8_t level)
{
    log_level = level;
}

void usk_log(uint8_t level, const char* format, ...)
{
    struct timespec t;
    va_list args;
    va_start(args,format);

    if (level & log_level)
    {
        (void)clock_gettime(CLOCK_MONOTONIC,&t);
        printf("[%lld.%.6ld] ",(long long)t.tv_sec,t.tv_nsec);
        vprintf(format,args);
        printf("\n");
    }

    va_end(args);
}




