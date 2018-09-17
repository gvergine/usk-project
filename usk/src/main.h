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

#ifndef MAIN_H_
#define MAIN_H_

#include "usk-plugin.h"
#include <stddef.h>

typedef struct plugins
{
    usk_plugin_ptr * elements;
    size_t len;
} plugins_t;


plugins_t * new_plugins();
void add_plugin(plugins_t *, usk_plugin_ptr plugin);
void remove_plugin(plugins_t * pl, usk_plugin_ptr plugin);
usk_plugin_ptr find_plugin(plugins_t *, const char * name);
void destroy_plugins(plugins_t *);

#endif /* MAIN_H_ */
