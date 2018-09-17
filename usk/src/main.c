/*
 * main.c
 *
 *  Created on: Sep 15, 2018
 *      Author: developer
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
