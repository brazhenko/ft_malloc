/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_free_block_from_cluster.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:14:11 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/19 23:21:03 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** [[used][used][used][      free      ]]
** 				||
** 				\/
** [[used][used][used][[ used  ][ free ]]
**
** extract_free_part()
** is called to 'cut' the free part during allocation
** and set all values need. This is an example of function anyone mustn't
** refactor :_)
*/

static void		extract_free_part(t_cluster *cluster,
		size_t need,
		void *ptr,
		t_block *tmp
)
{
	t_block		*block_to_set_free;

	block_to_set_free = ptr + sizeof(t_block) + need;
	block_to_set_free->size = tmp->size - need - sizeof(t_block);
	block_to_set_free->in_use = 0;
	tmp->size = need;
}

t_block			*get_free_block_from_cluster(t_cluster *cluster, size_t need)
{
	void		*ptr;
	t_block		*tmp;

	if (!cluster)
		return (NULL);
	ptr = ((void*)cluster) + sizeof(t_cluster);
	while (ptr < ((void*)cluster) + cluster->size)
	{
		tmp = (t_block*)ptr;
		if (!tmp->in_use && need <= tmp->size)
		{
			if (tmp->size > need + sizeof(t_block) + sizeof(char))
				extract_free_part(cluster, need, ptr, tmp);
			tmp->in_use = 1;
			// tmp->parent = cluster;
			cluster->count++;
			return (ptr + sizeof(t_block));
		}
		ptr += (sizeof(t_block) + tmp->size);
	}
	return (NULL);
}