/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:14:41 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/18 01:57:12 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_MALLOC_H
#define FT_MALLOC_MALLOC_H

# define LOGGER_AVAILABLE 1
#include "../memory.h"

# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>
#include <string.h>
#include <stdio.h>

#define FUNCNAME() // {\
//	printf(">");\
//    printf(__FUNCTION__); \
//	printf("\n"); \
//}

#define PTRPRT(P) {\
	printf("%s: %p | %zu\n", #P, P, (size_t)P);\
}
#define INTPRT(P) {\
	printf("%s: %d\n", #P, P);\
}
#define SIZEPRT(P) {\
	printf("%s: %zu\n", #P, P);\
}



/*
**	Zone type
*/

# define CLUSTER_TINY			0x0
# define CLUSTER_SMALL			0x1
# define CLUSTER_HUGE			0x2

# define TYNY_CLUSTER_LIMIT 	4096
# define SMALL_CLUSTER_LIMIT	8192

# define PAGES_PER_TINY_BLOCK	2
# define PAGES_PER_SMALL_BLOCK	16

typedef struct		s_cluster
{
	size_t				size;
	int					cluster_type;
	size_t				count;
	void				*end_;
	struct s_cluster	*prev;
	struct s_cluster	*next;
}					t_cluster;


typedef struct		s_block
{
	size_t				size;
	struct s_cluster	*parent;
	uint8_t				in_use;
}					t_block;

t_block		*get_next_block(t_block *block);
void		defragment_memory_start_from_block(t_block *block);
t_block		*get_free_block_from_cluster(t_cluster *cluster, size_t need);
t_cluster	*new_cluster(uint8_t cluster_type, size_t size);
int			is_block_valid(const void *ptr);

/*
**		memory acces protection
*/

void		lock_();
void		unlock_();

/*
**		main wrappers
*/

void		*realloc_(void *ptr, size_t size);
void		*malloc_(size_t size);
void		free_(void *ptr);

# if LOGGER_AVAILABLE

/*
 *		thread-safe logger
 */

# define LOG_FILE_FULL_PATH		"/tmp/com.lreznak-.malloc.log"
# define HEX_DUMP_FULL_PATH		"/tmp/com.lreznak-.malloc_hex_dump.log"
# define HEX_DUMP_FILE_CHANGED	"/tmp/com.lreznak-.malloc_hex_dump_.log"
int			alloc_logger(int status, void *ptr, size_t size);
void		mem_dump();

# endif

#endif //FT_MALLOC_MALLOC_H
