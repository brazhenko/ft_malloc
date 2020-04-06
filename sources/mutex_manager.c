//
// Created by 17641238 on 06.04.2020.
//

#include <pthread.h>

pthread_mutex_t		g_address_mutex;

void		lock_()
{
	static int	inited = 0;
	if (!inited)
		pthread_mutex_init(&g_address_mutex, NULL);
	pthread_mutex_lock(&g_address_mutex);
}

void		unlock_()
{
	pthread_mutex_unlock(&g_address_mutex);
}