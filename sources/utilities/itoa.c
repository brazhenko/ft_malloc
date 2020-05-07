/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 23:19:11 by a17641238         #+#    #+#             */
/*   Updated: 2020/05/06 21:47:43 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int		ft_numlen(int n, int minus)
{
	int numlen;

	numlen = 1;
	while ((n /= 10))
		numlen++;
	return (numlen + minus);
}

static int		abs_(int d)
{
	return (((d) < 0) ? (-(d)) : (d));
}

char			*itoa10(int n, char *out)
{
	char	*str;
	int		numlen;
	int		minus;
	int		digit;

	minus = (n < 0) ? 1 : 0;
	numlen = ft_numlen(n, minus);
	if ((str = out))
	{
		str[numlen--] = '\0';
		while (numlen >= minus)
		{
			digit = n % 10;
			str[numlen--] = abs_(digit) + '0';
			n /= 10;
		}
		if (minus)
			str[0] = '-';
	}
	return (str);
}

void			strrev(unsigned char *str)
{
	int				i;
	int				j;
	unsigned char	a;
	unsigned		len;

	len = ft_strlen((const char *)str);
	i = 0;
	j = len - 1;
	while (i < j)
	{
		a = str[i];
		str[i] = str[j];
		str[j] = a;
		i++;
		j--;
	}
}

int				itoa(int num, unsigned char *str, int len, int base)
{
	int		i;
	int		digit;

	i = 0;
	if (len == 0)
		return (-1);
	digit = num % base;
	if (digit < 0xA)
		str[i++] = '0' + digit;
	else
		str[i++] = 'A' + digit - 0xA;
	num /= base;
	while (num && (i < (len - 1)))
	{
		digit = num % base;
		str[i++] = 'A' + digit - (digit < 0xA ? 0 : 0xA);
		num /= base;
	}
	if (i == (len - 1) && num)
		return (-1);
	str[i] = '\0';
	strrev(str);
	return (0);
}

