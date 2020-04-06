//
// Created by 17641238 on 06.04.2020.
//
#include "malloc.h"

extern void* g_start_address;

static void 	insert_cluster_to_begin(t_cluster *cluster)
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

static void init_cluster_first_block(t_cluster *cluster)
{
	FUNCNAME()
	t_block		*first_block;

	first_block = ((void *)cluster) + sizeof(t_cluster);
	memset(first_block, 0, sizeof(t_block));
	first_block->size = cluster->size - sizeof(t_block);
}

t_cluster	*init_new_cluster(int cluster_type, size_t size)
{
	FUNCNAME()

	t_cluster	*ret;
	size_t		size_to_alloc;
	size_t		modulo;

	if (cluster_type == CLUSTER_TINY)
		size_to_alloc = PAGES_PER_TINY_BLOCK * getpagesize();
	else if (cluster_type == CLUSTER_SMALL)
		size_to_alloc = PAGES_PER_SMALL_BLOCK * getpagesize();
	else if (cluster_type == CLUSTER_HUGE)
	{
		modulo = getpagesize() - size % getpagesize();
		if (modulo <= sizeof(t_block))
			// проверяем, что хватит места, чтоб для инфы выделить место
			modulo += getpagesize();
		size_to_alloc = size + modulo;
	}
	else
		return (NULL);
	ret = cluster_alloc(size_to_alloc);
	if (!ret)
		return (ret);
	memset(ret, 0, sizeof(t_cluster));
	ret->size = size_to_alloc - sizeof(t_cluster);
	ret->end_ = ((void*)ret) + sizeof(t_cluster) + ret->size;
	ret->cluster_type = cluster_type;
	ret->count = 0;
	init_cluster_first_block(ret);
	insert_cluster_to_begin(ret);
	return (ret);
}