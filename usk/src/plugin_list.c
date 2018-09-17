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

#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

plugins_t * new_plugins()
{
    plugins_t * p = (plugins_t*)malloc(sizeof(plugins_t));
    p->elements = (usk_plugin_ptr*)malloc(sizeof(usk_plugin_ptr));
    *p->elements = 0;
    p->len = 1;
    return p;
}

void add_plugin(plugins_t * pl, usk_plugin_ptr plugin)
{
    size_t i;
    for(i = 0; i < pl->len; i++)
    {
        if (*(pl->elements+i) == 0)
        {
            printf("added plugin %p at address %p\n",(void*)plugin,(void*)(pl->elements+i));

            *(pl->elements+i) = plugin;
            return;
        }
    }
    // double
    usk_plugin_ptr * new_elements = (usk_plugin_ptr*)realloc(pl->elements, sizeof(usk_plugin_ptr)*pl->len*2);
    if (new_elements == 0) // error
    {
        printf("Error realloc\n");

    }
    else
    {
        pl->elements = new_elements;
        for(i = pl->len; i < pl->len*2; i++)
        {
            *(pl->elements+i) = 0;
        }
        //memset(pl->elements+pl->len, 0, pl->len);
        pl->len *= 2;
        printf("increase plugin list to capacity %lu\n",pl->len);

        add_plugin(pl, plugin);
    }

}

void remove_plugin(plugins_t * pl, usk_plugin_ptr plugin)
{
    size_t i;
    for(i = 0; i < pl->len; i++)
    {
        if (*(pl->elements+i) == plugin)
        {
            *(pl->elements+i) = 0;
        }
    }

}

usk_plugin_ptr find_plugin(plugins_t * pl, const char * name)
{
    size_t i;
    for(i = 0; i < pl->len; i++)
    {
        if (*(pl->elements+i) == 0) continue;

        if (strcmp(name, (*(pl->elements+i))->vtable->name) == 0)
        {
            return *(pl->elements+i);
        }
    }
    return 0;

}

void destroy_plugins(plugins_t * pl)
{
    size_t i;

    for(i = 0; i < pl->len; i++)
    {
        if (*(pl->elements+i) == 0) continue;

        free(*(pl->elements+i));
    }

    free(pl->elements);
    free(pl);
}
