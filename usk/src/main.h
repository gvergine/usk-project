/*
 * main.h
 *
 *  Created on: Sep 16, 2018
 *      Author: developer
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
