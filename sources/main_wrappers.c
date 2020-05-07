/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_wrappers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:14:30 by a17641238         #+#    #+#             */
/*   Updated: 2020/05/07 14:45:54 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	thread-safe version of malloc_
*/

void		*malloc(size_t size)
{
	void		*ret;
	write(2, "aloc\n", 5);

	lock_();
	ret = malloc_(size);
	unlock_();
	mem_dump();
	return (ret);
}

/*
**	thread-safe version of realloc_
*/

void		*realloc(void *ptr, size_t size)
{
	void		*ret;

	write(2, "real\n", 5);

	lock_();
	ret = realloc_(ptr, size);
	unlock_();
	mem_dump();
	return (ret);
}

/*
**	thread-safe version of free_
*/

void		free(void *ptr)
{
	write(2, "free\n", 5);

	lock_();
	free_(ptr);
	unlock_();
	mem_dump();
}
