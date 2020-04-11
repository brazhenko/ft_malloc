//
// Created by 17641238 on 06.04.2020.
//

#ifndef FT_MALLOC_UTILITIES_H
#define FT_MALLOC_UTILITIES_H

#include <stddef.h>

void	*memcpy_m(void *restrict dst, const void *restrict src, size_t n);
void	*memset_m(void *b, int c, size_t len);
void	*memmove_m(void *dst, const void *src, size_t len);

#endif //FT_MALLOC_UTILITIES_H
