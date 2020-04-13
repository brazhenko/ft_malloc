//
// Created by 17641238 on 03.04.2020.
//



#include "malloc.h"

extern void		*g_start_address;

static void	*find_free_block(int cluster_type, size_t size)
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

static int get_cluster_type_by_size(size_t size)
{
	if (0 <= size
			&& size <= TYNY_CLUSTER_LIMIT)
		return CLUSTER_TINY;
	else if ((TYNY_CLUSTER_LIMIT + 1) <= size
			&& size <= SMALL_CLUSTER_LIMIT)
		return CLUSTER_SMALL;
	return CLUSTER_HUGE;
}

void	*malloc_(size_t size)
{
	void *block;

	if (size == 0)
		return (NULL);

	// в каком кластере нам искать надо
	int cluster_type = get_cluster_type_by_size(size);

	// ищем в уже запрошенных у оси блоках
	block = find_free_block(cluster_type, size);

	if (block)
		return (block);

	// создаем новый кластер, g_start_address изменится
	t_cluster	*new_cluster = init_new_cluster(cluster_type, size);
	// забираем блок из кластера
	block = get_free_block_from_cluster(new_cluster, size);
	return (block);
}
