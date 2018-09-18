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

static const char prompt[3]   = "> \0";
static const char* cmd_exit = "exit";

extern struct usk_plugin_list plugins_list;

struct command
{
    const char * name;
    void (*function)(int, const char **);
};

void print_gpl_notice()
{
    puts(
            "usk Copyright (C) 2018  Giovanni Davide Vergine\n"
            "This program comes with ABSOLUTELY NO WARRANTY.\n"
            "This is free software, and you are welcome to redistribute it\n"
            "under the terms of GPLv3 license.\n"
    );
}

void command_load(int argc, const char * argv[])
{
    if (argc > 1)
    {
        puts("load: syntax: load <path to usk plugin>\n");
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
    if (argc > 1)
    {
        puts("unload: syntax: unload <plugin_name>\n");
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
        puts("plugins: syntax: plugins <no arguments>\n");
        return;
    }

    usk_plugin_ptr plugin;
    LIST_FOREACH(plugin,&plugins_list,pointers)
    {
        printf("%s\n",plugin->vtable->name);
    }
}

static struct command commands[] = {
        {"load", command_load},
        {"unload", command_unload},
        {"plugins", command_plugins},
        //		"create",
        //		"destroy",
        //		"loops",
        {0,0}
};



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

export_vtable_t exports = { "usk_shell", loop };

