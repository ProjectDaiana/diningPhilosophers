/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:29:09 by darotche          #+#    #+#             */
/*   Updated: 2024/07/16 17:43:08 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message_mtx(t_philo *philo, char *message, char *color)
{
	long elapsed_time;

	elapsed_time = get_elapsed_time(philo->data->start_time);
	pthread_mutex_lock(&philo->data->print_mutex);

	printf("%s%ld Philosopher %ld %s\n"RESET, color, elapsed_time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
