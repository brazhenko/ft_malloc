/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 22:16:06 by angavrel          #+#    #+#             */
/*   Updated: 2020/04/14 15:31:35 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

bool		malloc_error(const int err, const char *str)
{
	static const char	*msg[3] = {
		"  -> in _",
		"Invalid block: ",
		"mmap MAP_FAILED error: "
	};

	ft_dprintf(2, "%s%s\n", msg[err], str);
	return (false);
}
