#include "memory.h"
#include <fcntl.h>


int main(int argc, char **argv)
{
	char* ptr[100];

	for (int i = 1; i < 10; ++i)
	{
		ptr[i] = malloc(i);
	}
	show_alloc_mem();

	return 0;
}
