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

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <sys/queue.h>
#include "usk-plugin.h"
#include "usk-log.h"

void printk()
{
    printf("Hello from the user space kernel!\n");
}

struct usk_plugin_list plugins_list;

void unload_all_plugins()
{
    usk_plugin_ptr first;
    while(!LIST_EMPTY(&plugins_list))
    {
        first = LIST_FIRST(&plugins_list);
        unload(first);
    }
}

int main(int argc, char* argv[])
{
    (void) argc;
    set_usk_log_level(-1);
    usk_log(LOG_INFO, "usk init start");
    LIST_INIT(&plugins_list);

    usk_plugin_ptr plugin = load(argv[1]);

    if (plugin == 0)
    {
        return -1;
    }
    usk_log(LOG_INFO, "usk init done");

    plugin->vtable->loop();

    usk_log(LOG_INFO, "usk stopping");
    unload_all_plugins();
    usk_log(LOG_INFO, "usk gone");
    return 0;
}
