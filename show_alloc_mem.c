//
// Created by 17641238 on 03.04.2020.
//

#include <stdio.h>
#include "memory.h"

extern void* g_start_address;

void	show_alloc_mem(void)
{
	printf("==%s= g_start_address: %p | page_size: %d | sizeof(t_block): "
		"%zu | sizeof(t_cluster): %zu ===============\n", __FUNCTION__,
			g_start_address,
			getpagesize(),
			sizeof(t_block),
			sizeof(t_cluster)
					);
	const int page_size = getpagesize();
	t_cluster	*cluster = g_start_address;
	t_block		*lpblock;

	while (cluster)
	{
		printf("Cluster type: %d, Size: %zu, Count: %zu\n", cluster->cluster_type, cluster->size, cluster->count);
		lpblock = ((t_block*)(((void*)cluster) + sizeof(*cluster)));
		while ((void*)lpblock < ((void*)cluster) + cluster->size)
		{
			printf("%p | in_use: %d | size: %zu\n", lpblock, lpblock->in_use, lpblock->size);
			lpblock = ((void*)lpblock) + (sizeof(t_block) + lpblock->size);
		}
		// increment
		cluster = cluster->next;
	}
}