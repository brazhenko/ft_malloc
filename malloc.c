//
// Created by 17641238 on 03.04.2020.
//



#include "memory.h"
void		*g_start_address = NULL;

#include <sys/errno.h>

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>


void 	insert_cluster_to_begin(t_cluster *cluster)
{
	if (!g_start_address)
	{
		g_start_address = cluster;
		return ;
	}
	cluster->next = g_start_address;
	((t_cluster *)g_start_address)->prev = cluster;
	g_start_address = (void*)cluster;
}

void	*malloc(size_t size)
{
	FUNCNAME()

	int cluster_type = get_cluster_type_by_size(size);
	void *block = find_free_block(cluster_type, size);

	if (block)
		return (block);

	t_cluster	*new_cluster = init_new_cluster(cluster_type, size);


	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	FUNCNAME()
	return (NULL);
}

void	free(void *ptr)
{
	FUNCNAME()

	if (!ptr)
		return ;
	((t_block *)(ptr - sizeof(t_block)))->in_use = 0;
}

# define TESTFILE1 "testfile.txt"
# define TESTFILE2_O "test123.txt"
# define ALLOC_SIZE 100000

void	mmaptest()
{
	char* ptr_zone = mmap(0,
			1,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE,
			-1,
			0);

	// memset(ptr_zone, 0, ALLOC_SIZE);
	printf("%lld\n", (long long)ptr_zone);
}

