//
// Created by 17641238 on 06.04.2020.
//

#ifndef FT_MALLOC_MALLOC_H
#define FT_MALLOC_MALLOC_H

# define LOGGER_AVAILABLE 1
#include "../memory.h"

# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>
#include <string.h>
#include <stdio.h>

#define FUNCNAME() {\
	printf(">");\
    printf(__FUNCTION__); \
	printf("\n"); \
}

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
 * Zone type
 */

# define CLUSTER_TINY			0x0
# define CLUSTER_SMALL			0x1
# define CLUSTER_HUGE			0x2

# define TYNY_CLUSTER_LIMIT 	4096
# define SMALL_CLUSTER_LIMIT	8192

# define PAGES_PER_TINY_BLOCK	4
# define PAGES_PER_SMALL_BLOCK	8

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
	uint8_t				in_use;
	size_t				size;
	struct s_cluster	*parent;
}					t_block;

t_cluster	*cluster_alloc(size_t size);
void		cluster_free(t_cluster *cluster);
t_block		*get_next_block(t_block *block);
void		defragment_memory_start_from_block(t_block *block);
t_block		*get_free_block_from_cluster(t_cluster *cluster, size_t need);
t_cluster	*init_new_cluster(int cluster_type, size_t size);

/*
**		memory acces protection
*/

void		lock_();
void		unlock_();
void		*realloc_(void *ptr, size_t size);
void		*malloc_(size_t size);
void		free_(void *ptr);

# if LOGGER_AVAILABLE

/*
 *		thred-safe logger
 */

# define LOGFLODER				"/tmp"
# define LOGFILENAME			"com.lreznak-.malloc.log"
# define LOG_FILE_FULL_PATH		"/tmp/com.lreznak-.malloc.log"

int		alloc_logger(int status, void *ptr, size_t size);

# endif

#endif //FT_MALLOC_MALLOC_H
