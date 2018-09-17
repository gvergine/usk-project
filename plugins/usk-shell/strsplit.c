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

#include <string.h>
#include <stdlib.h>
#include "shell.h"

/* Based on this post on quora:
 * https://www.quora.com/How-do-you-write-a-C-program-to-split-a-string-by-a-delimiter-I-think-it-uses-ktochar
 */
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
