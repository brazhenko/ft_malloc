#include "memory.h"
#include <fcntl.h>
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))


int main(int argc, char **argv)
{


//	pthread_mutex_init(&g_mtx, NULL);
//
//	printf("main thread: %lu\n", (size_t)pthread_self());
//	pthread_t	t;
//	pthread_t	t1;
//	pthread_create(&t, NULL, &my_entry_function, NULL);
//	pthread_create(&t1, NULL, &my_entry_function, NULL);
//
//	int ret=pthread_join(t1, NULL);
//	printf("ret: %d\n", ret);
//	int ret2=pthread_join(t, NULL);
//	printf("ret: %d\n", ret2);

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
