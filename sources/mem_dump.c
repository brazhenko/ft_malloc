/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:14:46 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/21 19:53:42 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "malloc.h"
#include "utilities/utilities.h"

# define LOG_ENABLE

extern void		*g_start_address;

static void		bind_cluster_string(char *out, t_cluster *cluster)
{
	memcpy_(out, "C:0x", 4);
	itoa((int)cluster, (uint8_t*)(&out[0] + 4), sizeof(out), 16);
	strcat_(out, ":");
	itoa(cluster->size, (uint8_t*)(&out[0] + strlen(out)), sizeof(out), 10);
	strcat_(out, ":");
	if (cluster->cluster_type == CLUSTER_TINY)
		strcat_(out, "TYNY");
	else if (cluster->cluster_type == CLUSTER_SMALL)
		strcat_(out, "SMALL");
	else if (cluster->cluster_type == CLUSTER_HUGE)
		strcat_(out, "HUGE");
	else
		strcat_(out, "ERRORTYPE");
	out[strlen(out)] = '\n';
}

static void		bind_bock_string(char *out, t_block *block)
{
	memcpy_(out, "B:0x", 4);
	itoa((int)block, (uint8_t*)(&out[0] + 4), sizeof(out), 16);
	strcat_(out, ":");
	itoa((int)block->size, (uint8_t*)(&out[0] + strlen(out)), sizeof(out), 10);
	strcat_(out, ":");
	itoa(block->in_use, (uint8_t*)(&out[0] + strlen(out)), sizeof(out), 10);
	out[strlen(out)] = '\n';
}

static void		log_whole_structure(int dump_file_fd)
{
	t_cluster		*cluster;
	t_block			*block;
	char			format[128];

	cluster = g_start_address;
	while (cluster)
	{
		memset(format, 0, sizeof(format));
		bind_cluster_string(format, cluster);
		write(dump_file_fd, format, strlen(format));
		block = ((void*)cluster) + sizeof(t_cluster);
		while ((void*)block < cluster->end_)
		{
			memset(format, 0, sizeof(format));
			bind_bock_string(format, block);
			write(dump_file_fd, format, strlen(format));
			block = ((void*)block) + sizeof(t_block) + block->size;
		}
		cluster = cluster->next;
	}
}

void		mem_dump()
{
	static int	log_filed_inited = 0;
	int			dump_file;

	lock_();
	if (!log_filed_inited)
	{
		log_filed_inited = 1;
		dump_file = open(LOG_FILE_FULL_PATH,
				O_CREAT | O_WRONLY, 0644);
	}
	else
		dump_file = open(LOG_FILE_FULL_PATH,
				O_CREAT | O_WRONLY | O_APPEND, 0644);

	if (dump_file < 0)
	{
		perror(__FUNCTION__);
		return ;
	}
	log_whole_structure(dump_file);
	write(dump_file, "***\n", 4);
	close(dump_file);
	unlock_();
}

void	show_alloc_mem(void)
{
	lock_();
	log_whole_structure(STDERR_FILENO);
	write(STDERR_FILENO, "***\n", 4);
	unlock_();
}