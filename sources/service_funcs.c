//
// Created by 17641238 on 06.04.2020.
//
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