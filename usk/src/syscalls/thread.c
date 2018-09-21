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

#include "usk-thread.h"
#include <string.h>
#include "usk-log.h"
#include <stdlib.h>
#include <unistd.h>

void * thread_loop(usk_thread_ptr me)
{

	usleep(10000000);
	//..

    usk_log(LOG_DEBUG,"Thread %s ended",me->name);
    free(me->name);
	LIST_REMOVE(me, pointers);

    return 0;
}

extern struct usk_thread_list threads_list;

__attribute__ ((visibility("default")))
usk_thread_ptr start(const char* name)
{
	usk_thread_ptr t;
    LIST_FOREACH(t,&threads_list,pointers)
    {
        if (strcmp(t->name,name)==0)
        {
            usk_log(LOG_ERROR,"A thread with name %s already exists",name);
            return 0;
        }
    }

    t = (usk_thread_ptr)malloc(sizeof(usk_thread_t));
    t->name = strdup(name);

    LIST_INSERT_HEAD(&threads_list, t, pointers);
    usk_log(LOG_DEBUG,"Started thread %s",t->name);

    pthread_create(&t->thread,0,thread_loop,t);



    return t;
}

__attribute__ ((visibility("default")))
int stop(usk_thread_ptr thread)
{
    usk_log(LOG_DEBUG,"Stopping thread %s",thread->name);
    return 0;
}


