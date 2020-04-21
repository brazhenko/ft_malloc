/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 17:30:28 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/21 22:59:51 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "utilities/utilities.h"

#define PRINT_BYTES_PER_STRING	64

extern void		*g_start_address;

void	dump_block(t_block *lpblock)
{
	char		format[1024];
	unsigned	i;
	int			tmp;

	i = 0;
	tmp = mem_to_hex_brackets_endl(format, &lpblock, sizeof((*lpblock)), ' ');
	write(STDERR_FILENO, format, tmp);
	while (i < lpblock->size)
	{
		tmp = mem_to_hex_endl(format, ((void*)lpblock) + sizeof(t_block) + i,
		lpblock->size < PRINT_BYTES_PER_STRING + i ?
		lpblock->size % PRINT_BYTES_PER_STRING :
		PRINT_BYTES_PER_STRING, ' ');
		write(STDERR_FILENO, format, tmp);
		i += PRINT_BYTES_PER_STRING;
	}
}

void		show_mem_hex(void)
{
	t_cluster	*cluster;
	t_block		*lpblock;
	char		format[1024];
	int			tmp;

	cluster = g_start_address;
	while (cluster)
	{
		tmp = mem_to_hex_curly_endl(format, &cluster, sizeof(cluster), ' ');
		write(STDERR_FILENO, format, tmp);
		lpblock = ((t_block*)(((void*)cluster) + sizeof(t_cluster)));
		while ((void*)lpblock < (void*)cluster->end_)
		{
			if (lpblock->in_use)
				dump_block(lpblock);
			lpblock = ((void*)lpblock) + (sizeof(t_block) + lpblock->size);
		}
		cluster = cluster->next;
	}
}
