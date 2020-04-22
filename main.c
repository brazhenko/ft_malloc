#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "memory.h"

int main()
{
	void	*add[100];

	add[0] = malloc(1024);
	add[0] = malloc(1024);
	add[0] = malloc(1024);
	add[1] = malloc(214);
	add[0] = malloc(1024);



	add[2] = malloc(1234);
	add[2] = malloc(1234);

	free(add[1]);

	add[3] = malloc(132948);

	add[4] = malloc(12341);
	show_alloc_mem();
	return (0);
}
