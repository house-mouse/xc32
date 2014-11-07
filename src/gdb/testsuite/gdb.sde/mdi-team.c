/* This testcase is part of GDB, the GNU debugger.

   Copyright 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  
 
   This file is copied from watchthreads.c.  */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg); /* Pointer to function executed by each thread */

#define NUM 7

unsigned int args[NUM + 1];
volatile int flag[NUM + 1];

int main() {
    int res;
    pthread_t threads[NUM];
    void *thread_result;
    long i;

    for (i = 0; i < NUM; i++)
      {
	args[i] = 1; /* Init value.  */
	res = pthread_create(&threads[i],
		             NULL,
			     thread_function,
			     (void *) i);
      }

    args[i] = 1;
    thread_function ((void *) i);

    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    int my_number =  (long) arg;
    int *myp = (int *) &args[my_number];
    int go, i;

    /* Raise the flag and wait till all threads have risen.  */
    flag[my_number] = 1;
    do {
	go = 1;
	for (i = 0; i < NUM + 1; i++)
	    if (!flag[i])
		go = 0;
    } while (!go);

    /* Don't run forever.  Run just short of it :)  */
    while (*myp > 0)
      {
	(*myp) ++;  /* Loop increment.  */
      }

    pthread_exit(NULL);
}
