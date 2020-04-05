#ifndef FT_MALLOC_MEMORY_H
# define FT_MALLOC_MEMORY_H

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
	printf("%s: %p\n", #P, P);\
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

# define CLUSTER_TINY	0x0
# define CLUSTER_SMALL	0x1
# define CLUSTER_HUGE	0x2

# define TYNY_CLUSTER_LIMIT 	4096
# define SMALL_CLUSTER_LIMIT	8192

# define PAGES_PER_TINY_BLOCK	4
# define PAGES_PER_SMALL_BLOCK	8

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

void	*find_free_block(int cluster_type, size_t size);

typedef struct		s_cluster
{
	size_t				size;
	int					cluster_type;
	size_t				count;
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
	FUNCNAME()
	t_block		*first_block;

	first_block = ((void *)cluster) + sizeof(t_cluster);
	memset(first_block, 0, sizeof(t_block));
	first_block->size = cluster->size - sizeof(t_cluster) - sizeof(t_block);
}

static  t_block			*get_free_block_from_cluster(t_cluster *cluster, size_t need)
{
	FUNCNAME()

	void		*ptr = ((void*)cluster) + sizeof(t_cluster);
	t_block		*tmp;

	if (!cluster)
		return (NULL);
	while (ptr < ((void*)cluster) + cluster->size)
	{
		tmp = (t_block*)ptr;
		if (!tmp->in_use && need <= tmp->size)
		{
			if ( /* Остатка памяти хватает хоть на 1 t_block и еще 1 байт */
			tmp->size
			> sizeof(t_block) + sizeof(char)  + need + sizeof(t_block))
			{
				((t_block*)(ptr + sizeof(t_block) + need))->size
						= tmp->size - need - sizeof(t_block);
				((t_block*)(ptr + sizeof(t_block) + need))->in_use = 0;
			}
			tmp->size = need;
			tmp->in_use = 1;
			tmp->parent = cluster;
			cluster->count++;
			return (ptr + sizeof(t_block));
		}
		ptr += (sizeof(t_block) + tmp->size);
	}
	return (NULL);
}

static t_cluster	*init_new_cluster(int cluster_type, size_t size)
{
	FUNCNAME()

	t_cluster	*ret;
	size_t		size_to_alloc;
	size_t		modulo;

	if (cluster_type == CLUSTER_TINY)
		size_to_alloc = PAGES_PER_TINY_BLOCK * getpagesize();
	else if (cluster_type == CLUSTER_SMALL)
		size_to_alloc = PAGES_PER_SMALL_BLOCK * getpagesize();
	else if (cluster_type == CLUSTER_HUGE)
	{
		modulo = getpagesize() - size % getpagesize();
		if (modulo <= sizeof(t_block))
			// проверяем, что хватит места, чтоб для инфы выделить место
			modulo += getpagesize();
		size_to_alloc = size + modulo;
	}
	else
		return (NULL);
	ret = cluster_alloc(size_to_alloc);
	if (!ret)
		return (ret);
	memset(ret, 0, sizeof(t_cluster));
	ret->size = size_to_alloc;
	ret->cluster_type = cluster_type;
	ret->count = 0;
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
void			cluster_free(t_cluster *cluster);

#endif //FT_MALLOC_MEMORY_H

//mmap(2)
//munmap(2)
//getpagesize(3)
//getrlimit(2)
//The functions from libpthread
