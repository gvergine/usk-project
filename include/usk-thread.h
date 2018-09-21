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

#ifndef USK_THREAD_H_
#define USK_THREAD_H_

#include <sys/queue.h>
#include <pthread.h>

typedef struct usk_thread
{
    pthread_t thread;
    char * name;
    LIST_ENTRY(usk_thread) pointers;
} usk_thread_t;

typedef usk_thread_t * usk_thread_ptr;

LIST_HEAD(usk_thread_list, usk_thread);

usk_thread_ptr start(const char* name);
int stop(usk_thread_ptr thread);

#endif /* USK_THREAD_H_ */
