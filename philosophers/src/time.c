/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:50:42 by darotche          #+#    #+#             */
/*   Updated: 2024/07/05 17:50:49 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL))
		return (0);
	return (uint64_t)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

uint64_t get_elapsed_time(uint64_t start_time)
{
    return (get_time() - start_time);
}