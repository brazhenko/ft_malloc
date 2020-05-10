/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:15:23 by a17641238         #+#    #+#             */
/*   Updated: 2020/05/07 10:42:45 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "utilities/utilities.h"

void	*g_start_address;

static void	*cut_block(void *ptr, size_t size, t_block *current_block,
		t_block *next_block)
{
	next_block->size -= (size - current_block->size);
	memmove_(((void*)next_block) + (size - current_block->size),
			((void*)next_block), sizeof(t_block));
	current_block->size = size;
	return (ptr);
}

static void	*ret_n_free(void *ptr)
{
	free_(ptr);
	return (NULL);
}

static void	*aloc_and_copy(size_t size, void *ptr, t_block *current_block)
{
	void	*new_ptr;

	new_ptr = malloc_(size);
	if (!new_ptr)
		return (NULL);
	memcpy_(new_ptr, ptr, current_block->size);
	free_(ptr);
	return (new_ptr);
}

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

void		*realloc_(void *ptr, size_t size)
{
	void		*new_ptr;
	t_block		*current_block;
	t_cluster	*parent;
	t_block		*next_block;

	if (!ptr)
		return (malloc_(size));
	if (!is_block_valid(ptr, &parent))
		return (NULL);
	if (!size)
		return (ret_n_free(ptr));
	current_block = ptr - sizeof(t_block);
	if (size <= current_block->size)
		return (ptr);
	next_block = get_next_block(current_block, parent);
	if (next_block && !next_block->in_use)
	{
		defragment_memory_start_from_block(next_block, parent);
		if (next_block->size + sizeof(t_block) + current_block->size >= size)
			return (cut_block(ptr, size, current_block, next_block));
	}
	new_ptr = aloc_and_copy(size, ptr, current_block);
	return (new_ptr);
}
