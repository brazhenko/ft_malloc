/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 23:19:11 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/21 23:22:02 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void		strrev(unsigned char *str)
{
	int				i;
	int				j;
	unsigned char	a;
	unsigned		len;

	len = strlen((const char *)str);
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

int			itoa(int num, unsigned char *str, int len, int base)
{
	int		sum;
	int		i;
	int		digit;

	sum = num;
	i = 0;
	if (len == 0)
		return (-1);
	{
		digit = sum % base;
		if (digit < 0xA)
			str[i++] = '0' + digit;
		else
			str[i++] = 'A' + digit - 0xA;
		sum /= base;
	}
	while (sum && (i < (len - 1)))
	{
		digit = sum % base;
		if (digit < 0xA)
			str[i++] = '0' + digit;
		else
			str[i++] = 'A' + digit - 0xA;
		sum /= base;
	}
	if (i == (len - 1) && sum)
		return (-1);
	str[i] = '\0';
	strrev(str);
	return (0);
}
