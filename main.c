#include <stdio.h>
#include <dlfcn.h>
#include "memory.h"
#include <string.h>


int main()
{

	malloc(1);malloc(1);malloc(1);malloc(1);
	free(malloc(1));
	malloc(2);
	show_alloc_mem();
	malloc(1);


	malloc(4096 + 1);
	malloc(4096 + 2);


	free(malloc(8192 + 10));
	show_alloc_mem();
	return 0;
}
