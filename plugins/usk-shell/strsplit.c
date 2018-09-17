/*
 * strsplit.c
 *
 *  Created on: Sep 16, 2018
 *      Author: developer
 */
#include <string.h>
#include <stdlib.h>
#include "shell.h"

char** strsplit(const char* str, const char* delim, size_t* numtokens)
{
	char *s = strdup(str);
	size_t tokens_alloc = 1;
	size_t tokens_used = 0;
	char **tokens = calloc(tokens_alloc, sizeof(char*));
	char *token, *rest = s;
	while ((token = strsep(&rest, delim)) != 0)
	{
		if(strlen(token) == 0) continue;
		if (tokens_used == tokens_alloc)
		{
			tokens_alloc *= 2;
			tokens = realloc(tokens, tokens_alloc * sizeof(char*));
		}
		tokens[tokens_used++] = strdup(token);
	}
	if (tokens_used == 0)
	{
		free(tokens);
		tokens = 0;
	}
	else
	{
		tokens = realloc(tokens, tokens_used * sizeof(char*));
	}
	*numtokens = tokens_used;
	free(s);
    return tokens;
}
