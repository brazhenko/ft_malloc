//
// Created by 17641238 on 06.04.2020.
//

#include "malloc.h"

extern void	*g_start_address;

void	free_(void *ptr)
{
	FUNCNAME()

	if (!ptr)
		return ;

	t_block	*block;
	block = ((t_block *)(ptr - sizeof(t_block)));
	block->in_use = 0;

	// уменьшить счетчик занятых блоков
	t_cluster	*cluster = block->parent;
	cluster->count--;
	// перецепить указатели зон памяти
	if (cluster->count == 0)
	{
		if (block->parent->next)
			block->parent->next->prev = block->parent->prev;
		if (block->parent->prev)
			block->parent->prev->next = block->parent->next;
		if (cluster == g_start_address)
			g_start_address = cluster->next;
		cluster_free(cluster);
		return ;
	}

	// слить неиспользуемый передний блок для дефрагментации
	t_block		*next_block = (void*)block + sizeof(t_block) + block->size;
	if ((void*)next_block
			< ((void*)cluster) + sizeof(t_cluster) + cluster->size
			/* не вышло за пределеы кластера */
			&& !next_block->in_use
		/* И не в использовании */
			)
		block->size += (next_block->size + sizeof(t_block));
}