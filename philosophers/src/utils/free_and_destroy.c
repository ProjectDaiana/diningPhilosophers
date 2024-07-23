/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:23:39 by darotche          #+#    #+#             */
/*   Updated: 2024/07/23 19:44:51 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_ph)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
}

void	free_and_destroy(t_data *data)
{
	long	i;

	i = 0;
	while (i < data->n_of_ph)
	{
		pthread_mutex_destroy(&data->philo[i].ph_mutex);
		i++;
	}
	i = 0;
	while (i < data->n_of_ph)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->thr_running_mutex);
	pthread_mutex_destroy(&data->start_mutex);
	free(data->forks);
	free(data->philo);
}
