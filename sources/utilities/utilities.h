/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 23:23:51 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/22 17:40:12 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_UTILITIES_H
# define FT_MALLOC_UTILITIES_H

# include <stddef.h>

void	*memcpy_m(void *restrict dst, const void *restrict src, size_t n);
void	*memset_m(void *b, int c, size_t len);
void	*memmove_m(void *dst, const void *src, size_t len);

int		itoa(int num, unsigned char *str, int len, int base);
void	*memset_(void *b, int c, size_t len);
void	*memcpy_(void *dst, const void *src, size_t n);
char	*strcat_(char *s1, const char *s2);
void	*memmove_(void *dst, const void *src, size_t len);
char	*itoa10(int n, char *out);
size_t	ft_strlen(const char *s);

int		mem_to_hex(
		char *out,
		void *mem,
		size_t size,
		char separator);
int		mem_to_hex_endl(
		char *out,
		void *mem,
		size_t size,
		char separator);
int		mem_to_hex_brackets_endl(
		char *out,
		void *mem,
		size_t size,
		char separator);
int		mem_to_hex_curly_endl(
		char *out,
		void *mem,
		size_t size,
		char separator);

#endif
