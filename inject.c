//
// Created by 17641238 on 06.05.2020.
//
#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>
#include <syslog.h>

#include <stdio.h>
#include <syslog.h>

void *malloc(size_t size)
{
	fprintf(stderr, "allocating %lu bytes\n", (unsigned long)size);
	/* Do your stuff here */

	fprintf(stderr, "allocating %lu bytes\n", 2);
	fprintf(stderr, "allocating %lu bytes\n", (unsigned long)size);
	fprintf(stderr, "allocating %lu bytes\n", (unsigned long)size);

	return (void*)1;
}