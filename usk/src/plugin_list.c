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
