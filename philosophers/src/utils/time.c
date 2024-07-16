/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:50:42 by darotche          #+#    #+#             */
/*   Updated: 2024/07/16 17:28:07 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL))
		exit(1);
	return ((long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000)); // returns time in milliseconds
}

long get_elapsed_time(long start_time)
{
    return (get_time() - start_time);
}