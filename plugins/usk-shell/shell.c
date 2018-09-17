#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "shell.h"
#include "usk-plugin.h"

static const char prompt[3]   = "> \0";
static const char* cmd_exit = "exit";

struct command
{
	const char * name;
	void (*function)(int, const char **);
};

void command_load(int argc, const char * argv[])
{
	if (argc > 1)
	{
		puts("load: syntax: load <path to usk plugin>\n");
		return;
	}

	usk_plugin_ptr plugin;
	int ret = load(argv[0], &plugin);

	if (ret != 0)
	{
		printf("could not load %s\n",argv[0]);
		return;
	}


	plugin->vtable->loop();


}

static struct command commands[] = {
		{"load", command_load},
//		"unload",
//		"plugins",
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

