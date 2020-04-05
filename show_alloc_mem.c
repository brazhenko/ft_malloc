//
// Created by 17641238 on 03.04.2020.
//

#include <stdio.h>
#include "memory.h"

void	show_alloc_mem(void)
{
	FUNCNAME()
	const int pg_size = getpagesize();
	printf("%d\n", pg_size);
}