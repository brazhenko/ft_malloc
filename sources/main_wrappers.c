/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_wrappers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:14:30 by a17641238         #+#    #+#             */
/*   Updated: 2020/05/10 17:41:51 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	thread-safe version of malloc_
*/

void		*malloc(size_t size)
{
	void		*ret;
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
	lock_();
	free_(ptr);

	unlock_();
	mem_dump();
}
