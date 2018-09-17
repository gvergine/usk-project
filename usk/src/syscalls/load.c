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
#include <dlfcn.h>
#include <stdio.h>
#include "usk-plugin.h"
#include "main.h"

extern plugins_t * plugins;

int load(const char* path, usk_plugin_ptr *plugin)
{
    void *handle;
    char *error;
    export_vtable_t* imports;

    handle = dlopen (path, RTLD_NOW);

    if (!handle)
    {
        fputs (dlerror(), stderr);
        fputs ("\n", stderr);
        return -2;
    }

    imports = dlsym(handle, "exports");

    if ((error = dlerror()) != NULL)
    {
        dlclose(handle);
        fputs(error, stderr);
        fputs ("\n", stderr);
        return -3;
    }

    if (imports)
    {
        *plugin = (usk_plugin_ptr)malloc(sizeof(usk_plugin_t));
        (*plugin)->handle = handle;
        (*plugin)->vtable = imports;
        add_plugin(plugins, *plugin);
        printf("Loaded plugin %s\n",(*plugin)->vtable->name);
        return 0;
    }

    dlclose(handle);
    return -1;
}

int unload(const char* plugin_name)
{
    usk_plugin_ptr plugin = find_plugin(plugins, plugin_name);
    if (plugin == 0)
    {
        printf("Plugin %s not found\n",plugin_name);
        return -1;
    }
    printf("Unloading plugin %s\n",plugin->vtable->name);
    dlclose(plugin->handle);
    remove_plugin(plugins, plugin);
    free(plugin);
    return 0;
}

