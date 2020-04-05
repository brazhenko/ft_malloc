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

void	*find_free_block(int cluster_type, size_t size)
{
	FUNCNAME()
	t_cluster	*cluster;
	t_block		*free_block;

	if (cluster_type == CLUSTER_HUGE)
		return (NULL);
	if (!g_start_address)
		return (NULL);
	cluster = g_start_address;
	while (cluster)
	{
		if (cluster->cluster_type == cluster_type)
		{
			free_block = get_free_block_from_cluster(cluster, size);
			if (free_block)
				return (free_block);
		}
		// i++
		cluster = cluster->next;
	}
	return (NULL);
}

void	*malloc(size_t size)
{
	// в каком кластере нам искать надо
	int cluster_type = get_cluster_type_by_size(size);
	// ищем в уже запрошенных у оси блоках
	void *block = find_free_block(cluster_type, size);

	if (block)
		return (block);

	// создаем новый кластер, g_start_address изменится
	t_cluster	*new_cluster = init_new_cluster(cluster_type, size);
	// забираем блок с кластера
	block = get_free_block_from_cluster(new_cluster, size);

	return (block);
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
	t_block	*block;
	block = ((t_block *)(ptr - sizeof(t_block)));
	block->in_use = 0;
	t_cluster	*cluster = block->parent;
	cluster->count--;
	if (cluster->count == 0)
	{
		if (block->parent->next)
			block->parent->next->prev = block->parent->prev;
		if (block->parent->prev)
			block->parent->prev->next = block->parent->next;
		if (cluster == g_start_address)
			g_start_address = cluster->next;
		cluster_free(cluster);
	}
}
