/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:11:42 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/19 23:46:11 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		defragment_memory_start_from_block(t_block *block,
											t_cluster *block_parent)
{
	t_block		*next_block;

	next_block = get_next_block(block, block_parent);
	if (next_block && !next_block->in_use)
	{
		block->size += (sizeof(t_block) + next_block->size);
		defragment_memory_start_from_block(block, block_parent);
	}
}

t_block		*get_next_block(t_block *block, t_cluster *block_parent)
{
	t_block		*next_block;

	next_block = ((void*)block) + sizeof(t_block) + block->size;
	if ((void*)next_block < block_parent->end_)
		return (next_block);
	return (NULL);
}

/*
** is_block_valid()
** checks if [ptr] is a valid pointer. This check function is needed to
** pass checklist.
** Sets the parent cluster [out] if the [ptr] if valid NULL othervise.
*/

extern void		*g_start_address;

#define TRUE	1
#define FALSE	0

int		is_block_valid(const void *ptr, t_cluster** out)
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
			{
				if (out != NULL)
					*out = cluster;
				return (TRUE);
			}
			block = ((void*)block) + sizeof(t_block) + block->size;
		}
		cluster = cluster->next;
	}
	if (out != NULL)
		*out = NULL;
	return (FALSE);
}
