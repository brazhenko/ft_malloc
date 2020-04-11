//
// Created by 17641238 on 06.04.2020.
//

#include <stddef.h>
#include <stdint.h>

void	*memset_m(void *b, int c, size_t len)
{
	uint8_t		v;
	uint64_t	v_big;

	v = (uint8_t)c;
	v_big = (v << 12U) | (v << 8U) | (v << 4U) | (v << 0U);
	while (b + sizeof(uint64_t) < b + len)
	{
		*(uint64_t *)b = v_big;
		b += sizeof(uint64_t);
	}
	while (b < b + len)
	{
		*(uint64_t *)b = v;
		b += sizeof(uint8_t);
	}
	return (b);
}