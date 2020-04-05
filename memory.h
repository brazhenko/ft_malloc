#ifndef FT_MALLOC_MEMORY_H
# define FT_MALLOC_MEMORY_H

# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>
#include <string.h>

#define FUNCNAME() {\
    printf(__FUNCTION__); \
	printf("\n"); \
}

/*
 * Zone type
 */

# define CLUSTER_TINY	0x0
# define CLUSTER_SMALL	0x1
# define CLUSTER_HUGE	0x2

# define TYNY_CLUSTER_LIMIT 	4096
# define SMALL_CLUSTER_LIMIT	8192

# define PAGES_PER_TINY_BLOCK	2
# define PAGES_PER_SMALL_BLOCK	4

static int get_cluster_type_by_size(size_t size)
{
	if (0 <= size
			&& size <= TYNY_CLUSTER_LIMIT)
		return CLUSTER_TINY;
	else if ((TYNY_CLUSTER_LIMIT + 1) <= size
			&& size <= SMALL_CLUSTER_LIMIT)
		return CLUSTER_SMALL;
	return CLUSTER_HUGE;
}

static void	*find_free_block(int cluster_type, size_t size)
{
	if (cluster_type == CLUSTER_HUGE)
		return (NULL);

	return (NULL);
}

typedef struct		s_cluster
{
	size_t				size;
	struct s_cluster	*prev;
	struct s_cluster	*next;
}					t_cluster;


typedef struct		s_block
{
	uint8_t				in_use;
	size_t				size;
	struct s_cluster	*parent;
}					t_block;

t_cluster		*cluster_alloc(size_t size);
void 	insert_cluster_to_begin(t_cluster *cluster);

static void init_cluster_first_block(t_cluster *cluster)
{
	t_block		*first_block;

	first_block = ((void *)cluster) + sizeof(t_cluster);
	memset(first_block, 0, sizeof(t_block));
	first_block->size = cluster->size - sizeof(t_cluster) - sizeof(t_block);
}

static t_cluster	*init_new_cluster(int cluster_type, size_t size)
{
	t_cluster		*ret;
	size_t size_to_alloc;

	if (cluster_type == CLUSTER_TINY)
		size_to_alloc = PAGES_PER_TINY_BLOCK * getpagesize();
	else if (cluster_type == CLUSTER_SMALL)
		size_to_alloc = PAGES_PER_SMALL_BLOCK * getpagesize();
	else if (cluster_type == CLUSTER_HUGE)
		size_to_alloc = size;
	else
		return (NULL);
	ret = cluster_alloc(size_to_alloc);
	if (!ret)
		return (ret);
	memset(ret, 0, sizeof(t_cluster));
	ret->size = size;
	init_cluster_first_block(ret);
	insert_cluster_to_begin(ret);
	return (ret);
}



void	hello(void);
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();
void	mmaptest();

#endif //FT_MALLOC_MEMORY_H

//mmap(2)
//munmap(2)
//getpagesize(3)
//getrlimit(2)
//The functions from libpthread
