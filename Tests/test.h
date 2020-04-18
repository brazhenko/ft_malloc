#include <stdlib.h>

#pragma GCC diagnostic ignored "-Wunused-result"

int test1()
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
	return (0);
}

int test2()
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}

#include <stdlib.h>
int test3()
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
	return (0);
}
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#define M (1024 * 1024)

void print(char *s)
{
	write(1, s, strlen(s));
}

int test4()
{
	char *addr1;
	char *addr3;

	addr1 = (char*)malloc(16*M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char*)realloc(addr1, 128*M);
	addr3[127*M] = 42;
	print(addr3);
	return (0);
}
#include <strings.h>
#include <stdlib.h>

#define M (1024 * 1024)



int test5()
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = (char*)malloc(16*M);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr2 = (char*)malloc(16*M);
	addr3 = (char*)realloc(addr1, 128*M);
	addr3[127*M] = 42;
	print(addr3);
	return (0);
}


int test6()
{
	char *addr;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjours\n");
}

int test7()
{
	char *addr;

	addr = malloc(42);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 0) == NULL)
		print("Bonjours\n");
}

int test8()
{
	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}

# define MAKE_TEST(TEST) {\
	print(#TEST "\n");TEST();\
}

// usage
// MAKE_TEST(test1);