/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:50:42 by darotche          #+#    #+#             */
/*   Updated: 2024/07/22 19:33:58 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("Error: gettimeofday failed\n");
		exit (EXIT_FAILURE);
	}
	return ((long)(tv.tv_sec) *1000 + (tv.tv_usec / 1000));
}

long	get_elapsed_time(long start_time)
{
	return (get_time() - start_time);
}
