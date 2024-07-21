/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:23:39 by darotche          #+#    #+#             */
/*   Updated: 2024/07/21 15:27:06 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	destroy_mutex(t_data *data)
{
	int i;

	i = 0;
	while(i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
}

void	free_and_destroy(t_data *data)
{
	long i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->philo[i].ph_mutex);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->thr_running_mutex);
	pthread_mutex_destroy(&data->start_mutex);
	free(data->philo);
	free(data->forks);
}