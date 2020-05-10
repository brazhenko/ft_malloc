/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:14:46 by a17641238         #+#    #+#             */
/*   Updated: 2020/05/10 17:47:03 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "malloc.h"
#include "utilities/utilities.h"

extern void		*g_start_address;

static void		bind_cluster_string(char *out, t_cluster *cluster)
{
	memcpy_(out, "C:0x", 4);
	mem_to_hex((&out[0] + 4), &cluster, sizeof(cluster), '\0');
	strcat_(out, ":");
	itoa10((int)cluster->size, (char*)(&out[0] + ft_strlen(out)));
	strcat_(out, ":");
	if (cluster->cluster_type == CLUSTER_TINY)
		strcat_(out, "TYNY");
	else if (cluster->cluster_type == CLUSTER_SMALL)
		strcat_(out, "SMALL");
	else if (cluster->cluster_type == CLUSTER_HUGE)
		strcat_(out, "HUGE");
	else
		strcat_(out, "ERRORTYPE");
	out[ft_strlen(out)] = '\n';
}

static void		bind_block_string(char *out, t_block *block)
{
	memcpy_(out, "B:0x", 4);
	mem_to_hex((&out[0] + 4), &block, sizeof(block), '\0');
	strcat_(out, ":");
	itoa10((int)block->size, (char*)(&out[0] + ft_strlen(out)));
	strcat_(out, ":");
	itoa(block->in_use, (uint8_t*)(&out[0] + ft_strlen(out)), sizeof(out), 10);
	out[ft_strlen(out)] = '\n';
}

static void		log_whole_structure(int dump_file_fd)
{
	t_cluster		*cluster;
	t_block			*block;
	char			format[128];

	cluster = g_start_address;
	while (cluster)
	{
		memset_(format, 0, sizeof(format));
		bind_cluster_string(format, cluster);
		write(dump_file_fd, format, ft_strlen(format));
		block = ((void*)cluster) + sizeof(t_cluster);
		while ((void*)block < cluster->end_)
		{
			memset_(format, 0, sizeof(format));
			bind_block_string(format, block);
			write(dump_file_fd, format, ft_strlen(format));
			block = ((void*)block) + sizeof(t_block) + block->size;
		}
		cluster = cluster->next;
	}
}

void			mem_dump(void)
{
	static int	log_filed_inited = 0;
	int			dump_file;

	lock_();
	if (!log_filed_inited)
	{
		log_filed_inited = 1;
		dump_file = open(LOG_FILE_FULL_PATH,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
		dump_file = open(LOG_FILE_FULL_PATH,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (dump_file < 0)
	{
		return ;
	}
	log_whole_structure(dump_file);
	write(dump_file, "***\n", 4);
	close(dump_file);
	unlock_();
}

void			show_alloc_mem(void)
{
	lock_();
	log_whole_structure(STDERR_FILENO);
	write(STDERR_FILENO, "***\n", 4);
	unlock_();
}
