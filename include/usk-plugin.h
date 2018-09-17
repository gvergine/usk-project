/*
 * usk-plugin.h
 *
 *  Created on: Sep 15, 2018
 *      Author: developer
 */

#ifndef USK_PLUGIN_H_
#define USK_PLUGIN_H_

#include <sys/queue.h>

typedef struct usk_plugin
{
	void * handle;
	struct export_vtable * vtable;
} usk_plugin_t;

typedef usk_plugin_t * usk_plugin_ptr;

typedef struct export_vtable
{
   const char * name;
   void (*loop)(void);
} export_vtable_t;

void printk();

//syscalls
int load(const char* path, usk_plugin_ptr *plugin);
int unload(const char* plugin_name);


#endif /* USK_PLUGIN_H_ */
