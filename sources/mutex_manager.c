/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a17641238 <a17641238@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 00:15:18 by a17641238         #+#    #+#             */
/*   Updated: 2020/04/15 00:15:18 by a17641238        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

/*
** g_address_mutex
** Main mutex which is guarding alloca's private structures from data races.
**
** lock_()
** enables the guard
**
** unlock_()
** disables the guard
*/

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