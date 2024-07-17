/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:26:09 by darotche          #+#    #+#             */
/*   Updated: 2024/07/16 22:24:32 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_full(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philo[i].eat_count < data->num_of_meals)
			return (0);
		data->philo[i].full = true;
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_data *data = (t_data *)arg;

	while (1)
	{
		pthread_mutex_lock(&data->print_mutex);
		if (data->total_served >= data->num_of_meals && all_full(data) == 1)
		{
			data->start = false;
			printf(RED"Philosophers have eaten %ld times\n"RESET, data->total_served);
			pthread_mutex_unlock(&data->print_mutex);	
			return (NULL);
		}
		pthread_mutex_unlock(&data->print_mutex);
		
		pthread_mutex_lock(&data->print_mutex);
		if (data->dead_philo >= 0) 
		{
			data->start = false;
			printf(RED"PHILO %d IS DEAD!\n"RESET, data->dead_philo);
			return (NULL);
		}
		pthread_mutex_unlock(&data->print_mutex);
		usleep(100);
	}
}
