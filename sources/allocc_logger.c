//
// Created by 17641238 on 07.04.2020.
//


#include "malloc.h"
#if LOGGER_AVAILABLE

#include <pthread.h>
#include <fcntl.h>

# define SIZE_TO_MAP	4080
# define MINIMUM_OK_TO_WRITE	50
# define LOGGER_STATUS_FREE		0
# define LOGGER_STATUS_ALLOC	1

static pthread_mutex_t	logger_mtx;
static int fd = -1;
static size_t	offset = 0;
static size_t	bytes_left = SIZE_TO_MAP;
static const size_t 	bytes_per_write = sizeof(void*) + sizeof(size_t) + \
                                    sizeof(char);
void	logger_mtx_lock()
{
	static int		inited = 0;
	if (!inited)
		pthread_mutex_init(&logger_mtx, NULL);
	pthread_mutex_lock(&logger_mtx);
}

void	logger_mtx_unlock()
{
	pthread_mutex_unlock(&logger_mtx);
}



int		alloc_logger(int status, void *ptr, size_t size)
{
	int		ret;

	ret = 0;
	logger_mtx_lock();
	static void* to_write = NULL;
	if (fd < 0 && 0 < (fd = open(LOG_FILE_FULL_PATH, O_WRONLY | O_CREAT)))
		return (-1);

	if (!to_write)
	{
		to_write = mmap(NULL, SIZE_TO_MAP, PROT_WRITE, MAP_SHARED, fd, offset);
		bytes_left = SIZE_TO_MAP;
	}
	if (bytes_left < MINIMUM_OK_TO_WRITE)
	{
		munmap(to_write, SIZE_TO_MAP);

		to_write = mmap(NULL, SIZE_TO_MAP, PROT_WRITE, MAP_SHARED, fd, offset);
		bytes_left = SIZE_TO_MAP;
	}

	if (to_write == MAP_FAILED)
		return (-2);

	if (status == LOGGER_STATUS_ALLOC)
		memcpy(to_write + offset, "A", sizeof("A"));
	else if (status == LOGGER_STATUS_FREE)
		memcpy(to_write + offset, "F", sizeof("F"));
	memcpy(to_write + offset, &ptr, sizeof(void*));
	memcpy(to_write + offset, "ZZZZ", sizeof(void*));
	memcpy(to_write + offset, &size, sizeof(size_t));
	memcpy(to_write + offset, "XXXX", sizeof(size_t));
	bytes_left -= bytes_per_write;
	offset += bytes_per_write;

	logger_mtx_unlock();
	return (ret);
}

#endif