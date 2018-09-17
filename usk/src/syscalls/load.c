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
#include <string.h>
#include "usk-plugin.h"

extern struct usk_plugin_list plugins_list;

usk_plugin_ptr load(const char* path)
{
    void *handle;
    char *error;
    export_vtable_t* imports;
    usk_plugin_ptr plugin;

    handle = dlopen (path, RTLD_NOW);

    if (!handle)
    {
        fputs (dlerror(), stderr);
        fputs ("\n", stderr);
        return 0;
    }

    imports = dlsym(handle, "exports");

    if ((error = dlerror()) != NULL)
    {
        dlclose(handle);
        fputs(error, stderr);
        fputs ("\n", stderr);
        return 0;
    }

    if (imports)
    {
        plugin = (usk_plugin_ptr)malloc(sizeof(usk_plugin_t));
        plugin->handle = handle;
        plugin->vtable = imports;

        usk_plugin_ptr i;
        LIST_FOREACH(i,&plugins_list,pointers)
        {
            if (strcmp(i->vtable->name,plugin->vtable->name)==0)
            {
            	printf("A plugin with name %s already exist.\n",i->vtable->name);
                dlclose(handle);
                return i;
            }
        }

        LIST_INSERT_HEAD(&plugins_list, plugin, pointers);
        printf("Loaded plugin %s\n",plugin->vtable->name);
        return plugin;
    }

    dlclose(handle);
    return 0;
}

int unload(const char* name)
{
    usk_plugin_ptr plugin;
    LIST_FOREACH(plugin,&plugins_list,pointers)
    {
        if (strcmp(plugin->vtable->name,name)==0)
        {
            printf("Unloading plugin %s\n",plugin->vtable->name);
            dlclose(plugin->handle);
        	LIST_REMOVE(plugin, pointers);
            return 0;
        }
    }

    printf("Plugin %s not found\n",name);
    return -1;
}

