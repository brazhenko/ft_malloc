#include <stdlib.h>

int test0()
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
#include <stdlib.h>

int test1()
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

int test2()
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

#define M (1024 * 1024) 

void print(char *s) 
{ 
	write(1, s, strlen(s)); 
} 

int test3()
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

void print(char *s) 
{ 
	write(1, s, strlen(s)); 
} 


int test3bis()
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

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void print(char *s)
{
	write(1, s, strlen(s));
}

int test4()
{
	char *addr;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjours\n");
}
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void print(char *s)
{
	write(1, s, strlen(s));
}

int test4bis()
{
	char *addr;

	addr = malloc(42);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 0) == NULL)
		print("Bonjours\n");
}
#include <stdlib.h>

int test5()
{
	malloc(1024);
	malloc(1024 * 32);
	malloc(1024 * 1024);
	malloc(1024 * 1024 * 16);
	malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}
