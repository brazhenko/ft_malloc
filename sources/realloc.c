//
// Created by 17641238 on 06.04.2020.
//

#include "malloc.h"

void	*g_start_address;

/*
**	void *ptr:
** 	[ptr] - pointer to memory allocated by malloc()
**	size_t size:
**	[size] - size of bytes need to be reallocated
**
**	According to C11:
**	http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
**	1) if [ptr] == NULL realloc() returns malloc(size)
**	NOTE: if size == 0 behavior is relied on malloc
**	2) if [ptr] was malloced and [size] != 0 realloc tries to find [size] free
**		bytes and copy not more than [size] bytes if needed. If fails NULL
**		returned and ptr is NOT free()'d.
**	4) if [ptr] was not malloc()'ed or was free()'d behaviour is undefined
*/

void	*realloc_(void *ptr, size_t size)
{
	FUNCNAME()

	if (!ptr)
	{
		return (malloc(size));
	}

	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	t_block		*current_block = ptr - sizeof(t_block);

	if (size <= current_block->size)
	{
		return (ptr);
	}

	t_block	*next_block = get_next_block(current_block);
	if (next_block && !next_block->in_use)
	{
		defragment_memory_start_from_block(next_block);
		if (next_block->size + sizeof(t_block) + current_block->size >= size)
		{
			next_block->size -= (size - current_block->size);
			memmove(((void*)next_block) + (size - current_block->size),
					((void*)next_block), sizeof(t_block));
			current_block->size = size;
			return (ptr);
		}
	}
	else
	{
		void	*new_ptr = malloc(size);
		if (!new_ptr)
			return (NULL);
		memcpy(new_ptr, ptr + sizeof(t_block), current_block->size);
		free(ptr);
	}
	return (NULL);
}
