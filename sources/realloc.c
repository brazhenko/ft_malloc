/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:15:23 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/18 01:57:12 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*g_start_address;

/*
**	void *ptr:
** 	[ptr] - pointer to memory allocated by malloc()
**	size_t size:
**	[size] - size of bytes need to be reallocated
**
**	According to C standard:
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
	void		*new_ptr;
	t_block		*current_block = ptr - sizeof(t_block);

	if (!is_block_valid(ptr))
		return (NULL);
	if (!size)
	{
		free_(ptr);
		return (NULL);
	}
	if (size <= current_block->size)
		return (ptr);
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
	new_ptr = malloc_(size);
	if (!new_ptr)
		return (NULL);
	memcpy(new_ptr, ptr, current_block->size);
	free_(ptr);
	return (new_ptr);
}
