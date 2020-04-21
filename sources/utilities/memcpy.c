/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 11:42:18 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/21 23:24:30 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void		*memcpy_(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

void		*memset_(void *b, int c, size_t len)
{
	unsigned char *ptr;
	unsigned char sym;

	ptr = (unsigned char *)b;
	sym = (unsigned char)c;
	while (len--)
		*ptr++ = sym;
	return (b);
}

char		*strcat_(char *s1, const char *s2)
{
	char		*i;

	i = s1;
	while (*i)
		i++;
	while (*s2)
		*i++ = *s2++;
	*i = 0;
	return (s1);
}

void		*memmove_(void *dst, const void *src, size_t len)
{
	unsigned char			*my_dst;
	const unsigned char		*my_src;

	if (!dst && !src)
		return (NULL);
	my_dst = (unsigned char *)dst;
	my_src = (unsigned char *)src;
	if (my_src < my_dst)
	{
		while (len)
		{
			len--;
			*(my_dst + len) = *(my_src + len);
		}
	}
	else if (my_dst < my_src)
		memcpy_(dst, src, len);
	return (dst);
}
