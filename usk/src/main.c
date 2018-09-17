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
#include "main.h"

void printk()
{
    printf("Hello from the user space kernel!\n");
}

plugins_t * plugins;

int main(int argc, char* argv[])
{
    (void) argc;

    plugins = new_plugins();

    usk_plugin_ptr plugin;

    if (load(argv[1], &plugin) != 0)
    {
        return -1;
    }

    plugin->vtable->loop();

    // i dont like this
    size_t i;
    for(i = 0; i < plugins->len; i++)
    {
        plugin = *(plugins->elements+i);
        if (plugin == 0) continue;

        printf("Unloading plugin %s\n",plugin->vtable->name);
        dlclose(plugin->handle);
        remove_plugin(plugins, plugin);
        free(plugin);
    }
    //

    destroy_plugins(plugins);


    return 0;
}
