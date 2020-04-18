/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:11:42 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/17 14:23:53 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		defragment_memory_start_from_block(t_block *block)
{
	t_block		*next_block;

	next_block = get_next_block(block);
	if (next_block && !next_block->in_use)
	{
		block->size += (sizeof(t_block) + next_block->size);
		defragment_memory_start_from_block(block);
	}
}

t_block		*get_next_block(t_block *block)
{
	t_block		*next_block;

	next_block = ((void*)block) + sizeof(t_block) + block->size;
	if ((void*)next_block < block->parent->end_)
		return (next_block);
	return (NULL);
}

/*
 * is_block_valid()
 * checks if [ptr] is a valid pointer. This check function is needed to
 * pass checklist.
 */

extern void		*g_start_address;

#define TRUE	1
#define FALSE	0

int		is_block_valid(const void *ptr)
{
	t_cluster	*cluster;
	t_block		*block;

	if (!ptr)
		return (FALSE);
	cluster = g_start_address;
	while (cluster)
	{
		block = ((void*)cluster) + sizeof(t_cluster);
		while ((void*)block < ((void*)cluster) + cluster->size)
		{
			if (((void*)block + sizeof(t_block)) == ptr)
				return (TRUE);
			block = ((void*)block) + sizeof(t_block) + block->size;
		}
		cluster = cluster->next;
	}
	return (FALSE);
}
