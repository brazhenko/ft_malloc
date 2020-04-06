#include "memory.h"
#include <stdio.h>
#include <pthread.h>
#include <limits.h>

pthread_mutex_t		g_mtx;

void *my_entry_function(void *param)
{
	pthread_mutex_lock(&g_mtx);
	printf("new thread: %lu\n", (size_t)pthread_self());
	for (volatile int i = INT_MIN; i < INT_MAX; i++)
		;

	printf("hello\n");
	pthread_mutex_unlock(&g_mtx);
	return NULL;
}


int main()
{
	pthread_mutex_init(&g_mtx, NULL);

	printf("main thread: %lu\n", (size_t)pthread_self());
	pthread_t	t;
	pthread_t	t1;
	pthread_create(&t, NULL, &my_entry_function, NULL);
	pthread_create(&t1, NULL, &my_entry_function, NULL);

	int ret=pthread_join(t1, NULL);
	printf("ret: %d\n", ret);
	int ret2=pthread_join(t, NULL);
	printf("ret: %d\n", ret2);

//	char* ptr[100];
//
//	pthread_t t;
//	for (int i = 1; i < 10; ++i)
//	{
//		ptr[i] = malloc(i);
//	}
//	show_alloc_mem();
//
//	ptr[2] = realloc(ptr[2], 3);
//	ptr[1] = realloc(ptr[1], 2);
//	show_alloc_mem();
	return 0;
}
