/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cluster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 23:27:23 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/22 01:42:32 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "utilities/utilities.h"

extern void* g_start_address;

static t_cluster	*cluster_alloc(size_t size)
{
	t_cluster		*cluster;

	cluster = (t_cluster*)
			mmap(0,
					size,
					PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE,
					-1,
					0);
	if (cluster == MAP_FAILED)
		return (NULL);
	return (cluster);
}

static void			insert_cluster_to_begin(t_cluster *cluster)
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

static void			init_cluster_first_block(t_cluster *cluster)
{
	t_block		*first_block;

	first_block = ((void *)cluster) + sizeof(t_cluster);
	memset_(first_block, 0, sizeof(t_block));
	first_block->size = cluster->size - sizeof(t_block);
}

static void			init_cluster_data(const int cluster_type,
		t_cluster *ret,
		const size_t size_to_alloc)
{
	memset_(ret, 0, sizeof(t_cluster));
	ret->size = size_to_alloc - sizeof(t_cluster);
	ret->end_ = ((void*)ret) + sizeof(t_cluster) + ret->size;
	ret->cluster_type = cluster_type;
	ret->count = 0;
	init_cluster_first_block(ret);
	insert_cluster_to_begin(ret);
}

/*
** new_cluster()
** inits and puts new cluster to a private data structure.
*/

t_cluster			*new_cluster(uint8_t cluster_type, size_t size)
{
	t_cluster	*ret;
	size_t		size_to_alloc;
	size_t		modulo;
	const int	page_size = getpagesize();

	if (cluster_type == CLUSTER_TINY)
		size_to_alloc = PAGES_PER_TINY_BLOCK * getpagesize();
	else if (cluster_type == CLUSTER_SMALL)
		size_to_alloc = PAGES_PER_SMALL_BLOCK * getpagesize();
	else if (cluster_type == CLUSTER_HUGE)
	{
		modulo = page_size - size % page_size;
		if (modulo <= sizeof(t_block))
			modulo += page_size;
		size_to_alloc = size + modulo;
	}
	else
		return (NULL);
	ret = cluster_alloc(size_to_alloc);
	if (!ret)
		return (ret);
	init_cluster_data(cluster_type, ret, size_to_alloc);
	return (ret);
}
