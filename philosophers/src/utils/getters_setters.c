/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:27:37 by darotche          #+#    #+#             */
/*   Updated: 2024/07/23 15:09:19 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mtx, bool *dest, bool val)
{
	pthread_mutex_lock(mtx);
	*dest = val;
	pthread_mutex_unlock(mtx);
}

bool	get_bool(pthread_mutex_t *mtx, bool *val)
{
	bool	res;

	pthread_mutex_lock(mtx);
	res = *val;
	pthread_mutex_unlock(mtx);
	return (res);
}

void	set_long(pthread_mutex_t *mtx, long *dest, long val)
{
	pthread_mutex_lock(mtx);
	*dest = val;
	pthread_mutex_unlock(mtx);
}

long	get_long(pthread_mutex_t *mtx, long *val)
{
	long	res;

	pthread_mutex_lock(mtx);
	res = *val;
	pthread_mutex_unlock(mtx);
	return (res);
}

void	increase_long(pthread_mutex_t *mutex, long *val)
{
	pthread_mutex_lock(mutex);
	(*val)++;
	pthread_mutex_unlock(mutex);
}
