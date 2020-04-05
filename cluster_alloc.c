//
// Created by 17641238 on 05.04.2020.
//

#include "memory.h"

t_cluster		*cluster_alloc(size_t size)
{
	t_cluster		*cluster;

	cluster = (t_cluster*)
			mmap(0,
			size,
			PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE,
			-1,
			0);
	if (MAP_FAILED == cluster)
		return (NULL);
	return (cluster);
}

void			cluster_free(t_cluster *cluster)
{
	munmap(cluster, cluster->size);
}