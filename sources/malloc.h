/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:14:41 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/21 23:06:32 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_MALLOC_H
# define FT_MALLOC_MALLOC_H

# define LOGGER_AVAILABLE 1

# include "../memory.h"

# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>
# include <string.h>
# include <stdio.h>

/*
**	Zone type
*/

# define CLUSTER_TINY			0x0
# define CLUSTER_SMALL			0x1
# define CLUSTER_HUGE			0x2

# define TYNY_CLUSTER_LIMIT 	4096
# define SMALL_CLUSTER_LIMIT	8192

# define PAGES_PER_TINY_BLOCK	16
# define PAGES_PER_SMALL_BLOCK	32

/*
** struct		s_cluster
**
** This structure represents the data stored about each cluster
** where [struct s_block]s are stored.
*/

typedef struct	s_cluster
{
	size_t				size;
	size_t				count;
	void				*end_;
	struct s_cluster	*prev;
	struct s_cluster	*next;
	uint8_t				cluster_type;
}				t_cluster;

/*
** struct		s_block
**
** This structure represents the data stored about each `pointer`
** returned by malloc/realloc.
*/

typedef struct	s_block
{
	unsigned		size;
	uint8_t			in_use;
}				t_block;

t_block			*get_next_block(t_block *block, t_cluster *block_parent);
void			defragment_memory_start_from_block(t_block *block,
													t_cluster *block_parent);
t_block			*get_free_block_from_cluster(t_cluster *cluster, size_t need);
t_cluster		*new_cluster(uint8_t cluster_type, size_t size);
int				is_block_valid(const void *ptr, t_cluster **out);

/*
**	memory access protection
*/

void			lock_();
void			unlock_();

/*
**	thread-UNSAFE versions if lib malloc/readlloc/free functions
*/

void			*realloc_(void *ptr, size_t size);
void			*malloc_(size_t size);
void			free_(void *ptr);

# if LOGGER_AVAILABLE

/*
**		thread-safe logger
*/

#  define LOG_FILE_FULL_PATH	"/tmp/com.lreznak-.malloc.log"

void			mem_dump();

# endif

#endif
