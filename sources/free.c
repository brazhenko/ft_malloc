/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:13:57 by a17641238         #+#    #+#             */
/*   Updated: 2020/05/09 17:57:06 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

extern void	*g_start_address;

static void		cluster_free(t_cluster *cluster)
{
	munmap(cluster, cluster->size);
}

static void		erase_cluster(t_cluster *cluster)
{
	if (cluster->next)
		cluster->next->prev = cluster->prev;
	if (cluster->prev)
		cluster->prev->next = cluster->next;
	if (cluster == g_start_address)
		g_start_address = cluster->next;
	cluster_free(cluster);
}

void			free_(void *ptr)
{
	t_cluster		*cluster;
	t_block			*block;
	t_cluster		*parent;

	if (!is_block_valid(ptr, &parent))
		return ;
	block = ((t_block *)(ptr - sizeof(t_block)));
	block->in_use = 0;
	cluster = parent;
	cluster->count--;
	if (cluster->count == 0 && cluster->cluster_type == CLUSTER_HUGE)
	{
		erase_cluster(cluster);
		return ;
	}
	defragment_memory_start_from_block(block, parent);
}
