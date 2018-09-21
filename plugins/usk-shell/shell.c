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
#include <readline/readline.h>
#include <readline/history.h>

#include "shell.h"
#include "usk-plugin.h"
#include "usk-thread.h"

static const char prompt[3]   = "> \0";
static const char* cmd_exit = "exit";

extern struct usk_plugin_list plugins_list;
extern struct usk_thread_list threads_list;

struct command
{
    const char * name;
    void (*function)(int, const char **);
    const char * description;
};

void print_gpl_notice()
{
    puts(
            "usk-shell Copyright (C) 2018  Giovanni Davide Vergine\n"
            "This program comes with ABSOLUTELY NO WARRANTY.\n"
            "This is free software, you are welcome to redistribute\n"
    		"it under the terms of GPLv3 license."
    );
}

void command_load(int argc, const char * argv[])
{
    if (argc != 1)
    {
        puts("load: syntax: load <path to usk plugin>");
        return;
    }

    usk_plugin_ptr plugin = load(argv[0]);

    if (plugin == 0)
    {
        printf("could not load %s\n",argv[0]);
        return;
    }


    plugin->vtable->loop();


}

usk_plugin_ptr find_plugin_with_name(const char* name)
{
    usk_plugin_ptr plugin;
    LIST_FOREACH(plugin,&plugins_list,pointers)
    {
        if (strcmp(plugin->vtable->name,name)==0)
        {
            return plugin;
        }
    }
    return 0;
}

void command_unload(int argc, const char * argv[])
{
    if (argc != 1)
    {
        puts("unload: syntax: unload <plugin_name>");
        return;
    }

    usk_plugin_ptr plugin = find_plugin_with_name(argv[0]);

    if (plugin == 0)
    {
        printf("could not find plugin %s\n",argv[0]);
        return;
    }

    unload(plugin);

}

void command_plugins(int argc, const char * argv[])
{
    if (argc > 0)
    {
        puts("plugins: syntax: plugins <no arguments>");
        return;
    }

    usk_plugin_ptr plugin;
    LIST_FOREACH(plugin,&plugins_list,pointers)
    {
        printf("%s\n",plugin->vtable->name);
    }
}

void command_start(int argc, const char * argv[])
{
    if (argc != 1)
    {
        puts("start: syntax: start <thread name>");
        return;
    }

    usk_thread_ptr thread = start(argv[0]);

    if (thread == 0)
    {
        printf("could not start thread %s\n",argv[0]);
        return;
    }

}

usk_thread_ptr find_thread_with_name(const char* name)
{
	usk_thread_ptr t;
    LIST_FOREACH(t,&threads_list,pointers)
    {
        if (strcmp(t->name,name)==0)
        {
            return t;
        }
    }
    return 0;
}


void command_stop(int argc, const char * argv[])
{
    if (argc != 1)
    {
        puts("stop: syntax: stop <thread name>");
        return;
    }

    usk_thread_ptr t = find_thread_with_name(argv[0]);

    if (t == 0)
    {
        printf("could not find thread %s\n",argv[0]);
        return;
    }

    stop(t);

}

void command_threads(int argc, const char * argv[])
{
    if (argc > 0)
    {
        puts("threads: syntax: threads <no arguments>");
        return;
    }

    usk_thread_ptr t;
    LIST_FOREACH(t,&threads_list,pointers)
    {
        printf("%s\n",t->name);
    }

}

void command_help(int argc, const char * argv[]);

static struct command commands[] = {
        {"help", command_help, "print this help"},
        {"load", command_load, "load a plugin from filesystem"},
        {"unload", command_unload, "unload a plugin"},
        {"plugins", command_plugins, "list loaded plugins"},
		{"start", command_start, "start a worker thread"},
		{"stop", command_stop, "stop a worker thread"},
		{"threads", command_threads, "list worker threads"},
        {0,0,0}
};


void command_help(int argc, const char * argv[])
{
    int i = 0;
    struct command c = commands[i];
    while (c.name != 0)
    {
        printf("%s - %s\n",c.name,c.description);
        i++;
        c = commands[i];
    }

}


void process(char * input)
{
    struct command * c;
    size_t numwords;
    char** vec = strsplit(input, " \t",&numwords);
    if (numwords == 0) return;
    for(c = commands; c->name != 0; c++)
    {
        if (strcmp(c->name,vec[0])==0)
        {
            c->function((int)(numwords-1),(const char**)&vec[1]);
            return;
        }
    }
    printf("%s: no such command\n", vec[0]);
}


void loop()
{
    print_gpl_notice();
    puts("Press Ctrl+c to Exit");

    while(1)
    {
        char* input = readline(prompt);

        if (input == 0)
        {
            goto end;
        }

        if((strcmp(input,cmd_exit) == 0))
        {
            free(input);
            goto end;
        }

        add_history(input);
        process(input);
        free(input);
    }
    end:
    puts("Goodbye!");
    return;

}

__attribute__ ((visibility("default")))
export_vtable_t exports = { "usk_shell", loop };

