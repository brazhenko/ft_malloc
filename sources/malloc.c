/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:14:38 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/17 23:01:44 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern void		*g_start_address;

static void		*find_free_block(const int cluster_type, const size_t size)
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
		cluster = cluster->next;
	}
	return (NULL);
}

static uint8_t	get_cluster_type_by_required_size(const size_t size)
{
	if (0 <= size
			&& size <= TYNY_CLUSTER_LIMIT)
		return CLUSTER_TINY;
	else if ((TYNY_CLUSTER_LIMIT + 1) <= size
			&& size <= SMALL_CLUSTER_LIMIT)
		return CLUSTER_SMALL;
	return CLUSTER_HUGE;
}

void			*malloc_(size_t size)
{
	const uint8_t cluster_type = get_cluster_type_by_required_size(size);
	void *block;

	if (size == 0)
		return (NULL);
	block = find_free_block(cluster_type, size);
	if (block)
		return (block);
	// создаем новый кластер, g_start_address изменится
	t_cluster	*cluster = new_cluster(cluster_type, size);
	// забираем блок из кластера
	block = get_free_block_from_cluster(cluster, size);
	return (block);
}
