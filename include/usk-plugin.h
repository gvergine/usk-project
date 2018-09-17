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

#ifndef USK_PLUGIN_H_
#define USK_PLUGIN_H_

#include <sys/queue.h>

typedef struct usk_plugin
{
    void * handle;
    struct export_vtable * vtable;
    LIST_ENTRY(usk_plugin) pointers;
} usk_plugin_t;

typedef usk_plugin_t * usk_plugin_ptr;

LIST_HEAD(usk_plugin_list, usk_plugin);

typedef struct export_vtable
{
    const char * name;
    void (*loop)(void);
} export_vtable_t;

void printk();

//syscalls
usk_plugin_ptr load(const char* path);
int unload(const char* name);


#endif /* USK_PLUGIN_H_ */
