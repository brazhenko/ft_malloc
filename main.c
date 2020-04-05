#include <stdio.h>
#include <dlfcn.h>
#include "memory.h"
#include <string.h>


int main()
{
	malloc(1);
	realloc(NULL, 2);
	free(NULL);

	char buf[10];
	memset(buf, 0, sizeof(buf));
	do{
		mmaptest();
		read(0, buf, sizeof(buf));
	}
	while (!strncmp(buf, "r", 1));
	return 0;
}