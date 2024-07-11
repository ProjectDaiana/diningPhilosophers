/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:26:09 by darotche          #+#    #+#             */
/*   Updated: 2024/07/11 20:50:47 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_full(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philo[i].eat_count < data->total_meals)
			return (0);
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
		if (data->total_served > data->total_meals && all_full(data) == 1)
		{
			printf("All philosophers have eaten %ld times\n", data->total_served);
			exit(0);
		}
		if (data->dead_philo == true) 
		{
			printf(RED"PHILO IS DEAD!\n"RESET);
			exit(0);
		}
		pthread_mutex_unlock(&data->print_mutex);	
	}
}
// if  (philo->last_eat_time < data->time_to_die + data->start_time)
// {
// 	printf(RED"Philosopher %d is dead\n"RESET, philo->left_fork);
// 	data->dead_philo = true;	
// 	pthread_mutex_unlock(&data->forks[philo->left_fork]);	
// 	pthread_mutex_unlock(&data->forks[philo->right_fork]);
// 	return (NULL);
// }