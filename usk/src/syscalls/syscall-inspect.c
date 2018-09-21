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

#define _GNU_SOURCE

#include "usk-log.h"
#include <dlfcn.h>
#include <stdio.h>

typedef int (*orig_open_f_type)(const char *pathname, int flags);
static orig_open_f_type orig_open;

void init_wrappers()
{
    orig_open = (orig_open_f_type)dlsym(RTLD_NEXT,"open");
}

__attribute__ ((visibility("default")))
int open(const char *pathname, int flags)
{
    usk_log(LOG_INFO, "proxying open");
    return orig_open(pathname,flags);
}

