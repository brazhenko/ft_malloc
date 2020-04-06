//
// Created by 17641238 on 06.04.2020.
//

#include "malloc.h"

t_block			*get_free_block_from_cluster(t_cluster *cluster, size_t need)
{
	FUNCNAME()

	void		*ptr = ((void*)cluster) + sizeof(t_cluster);
	t_block		*tmp;

	if (!cluster)
		return (NULL);
	while (ptr < ((void*)cluster) + cluster->size)
	{
		tmp = (t_block*)ptr;
		if (!tmp->in_use && need <= tmp->size)
		{
			if ( /* Остатка памяти хватает хоть на 1 t_block и еще 1 байт */
					tmp->size
							> sizeof(t_block) + sizeof(char)  + need + sizeof(t_block))
			{
				((t_block*)(ptr + sizeof(t_block) + need))->size
						= tmp->size - need - sizeof(t_block);
				((t_block*)(ptr + sizeof(t_block) + need))->in_use = 0;
				((t_block*)(ptr + sizeof(t_block) + need))->parent = cluster;
			}
			tmp->size = need;
			tmp->in_use = 1;
			tmp->parent = cluster;
			cluster->count++;
			return (ptr + sizeof(t_block));
		}
		ptr += (sizeof(t_block) + tmp->size);
	}
	return (NULL);
}