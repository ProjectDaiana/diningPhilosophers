/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:26:09 by darotche          #+#    #+#             */
/*   Updated: 2024/07/17 23:43:28 by darotche         ###   ########.fr       */
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

bool	all_thr_running(pthread_mutex_t	*mutex, long *threads, long num_of_philos)
{
	bool ret;
	
	ret = false;

	pthread_mutex_lock(mutex);
	if (*threads == num_of_philos)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

bool	ph_died(t_philo *philo)
{
	long time;

	time = get_time() - philo->last_eat_time;
	if (get_bool(&philo->ph_mutex, &philo->full))
		return (false);
	printf(RED"Time since last eat: %ld\n"RESET, time);
	printf(RED"Time to die: %ld\n"RESET, philo->data->time_to_die);
	if(time > philo->data->time_to_die)
		return (true);
	return (false);
}

void	*monitor(void *arg)
{
	t_data *data;
	int i;

	data = (t_data *)arg;
	// while(!all_thr_running(&data->total_served_mutex, &data->total_served, data->num_of_philos))
	// 	;
	// pthread_mutex_lock(&data->print_mutex);
	 printf("Checking threads: %ld / %ld\n", data->total_served, data->num_of_philos);
	 printf(RED"Total served = %ld\n"RESET, data->total_served);
	// pthread_mutex_unlock(&data->print_mutex);
	print_message_mtx(data->philo, "Monitoring all threads are running", WHT);
	while (get_bool(&data->total_served_mutex, &data->end) == false)
	{
		i = 0;
		while (i < data->num_of_philos && !data->end)
		{
			printf(RED"Monitoring philo \n"RESET);
			if (ph_died(data->philo + i) == true)
			{
				set_bool(&data->total_served_mutex, &data->end, true);
				print_message_mtx(data->philo, "is dead", RED);
			}
			i++;
		}
	}
	return (NULL);
}
