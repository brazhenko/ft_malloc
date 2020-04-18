/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:14:46 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/15 00:14:46 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// # define HEX_DUMP_ENABLE
# define LOG_ENABLE

extern void		*g_start_address;

static void	dump_hex_to_file(FILE* f, t_block *block)
{
	uint8_t		*ptr;
	size_t		i;

	ptr = ((void*)block) + sizeof(t_block);
	i = 0;
	while (i < block->size)
	{
		fprintf(f, "%x ", ptr[i]);
		i++;
	}
	fprintf(f, "\n");
}

void		mem_dump()
{FUNCNAME()
	lock_();
	t_cluster	*cluster;
	t_block		*block;

	static int init = 0;
	FILE*		dump;
	FILE*		hex_dump;

	if (! init)
	{
		init = 1;
		dump = fopen(LOG_FILE_FULL_PATH, "w");
	}
	else
		dump = fopen(LOG_FILE_FULL_PATH, "a");

	hex_dump = fopen(HEX_DUMP_FULL_PATH, "w");

	if (!dump || !hex_dump)
		return;

	cluster = g_start_address;

	while (cluster)
	{
		fprintf(dump, "C:%p:%zu\n", cluster, cluster->size);
		fprintf(hex_dump, "C:%p:%zu\n", cluster, cluster->size);
		block = ((void*)cluster) + sizeof(t_cluster);
		while ((void*)block < ((void*)cluster) + cluster->size)
		{
			fprintf(dump, "B:%p:%zu:%d\n", block, block->size, block->in_use);
#ifdef HEX_DUMP_ENABLE
			fprintf(hex_dump, "%p\n", block);
			dump_hex_to_file(hex_dump, block);
#endif
			block = ((void*)block) + sizeof(t_block) + block->size;
		}
		cluster = cluster->next;
	}
	fprintf(dump, "***\n");

	fclose(dump);
	fclose(hex_dump);

	unlock_();
}