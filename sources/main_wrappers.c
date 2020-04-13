//
// Created by 17641238 on 06.04.2020.
//

#include "malloc.h"

void		*malloc(size_t size)
{
	void		*ret;

	lock_();
	ret = malloc_(size);
	unlock_();
	mem_dump();
	return (ret);
}

void		*realloc(void *ptr, size_t size)
{
	void		*ret;

	lock_();
	ret = realloc_(ptr, size);
	unlock_();
	mem_dump();
	return (ret);
}

void		free(void *ptr)
{
	lock_();
	free_(ptr);
	unlock_();
	mem_dump();
}