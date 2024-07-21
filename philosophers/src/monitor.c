/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:26:09 by darotche          #+#    #+#             */
/*   Updated: 2024/07/21 17:40:20 by darotche         ###   ########.fr       */
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
	long elapsed_time;	
	elapsed_time = get_elapsed_time(philo->last_eat_time);

	printf(RED"time %ld\n"RESET, elapsed_time);

	if (get_bool(&philo->ph_mutex, &philo->full))
	{
		printf(RED"Philo %ld is full and wont die\n"RESET, philo->id);
		return (false);
	}
	printf(RED"Time since last eat: %ld\n"RESET, elapsed_time);
	printf(RED "Time to die: %ld ms\n" RESET, philo->data->time_to_die);
	if(elapsed_time > philo->data->time_to_die)
		return (true);
	return (false);
}

void	*monitor(void *arg)
{
	t_data *data;
	int i;

	data = (t_data *)arg;
	while(!all_thr_running(&data->thr_running_mutex, &data->thr_running, data->num_of_philos))
		;
	printf("%ld Running\n", data->thr_running);
	pthread_mutex_lock(&data->print_mutex);
	printf("Monitoring started\n");
	pthread_mutex_unlock(&data->print_mutex);
	// pthread_mutex_lock(&data->print_mutex);
	//  printf("Checking threads: %ld / %ld\n", data->thr_running, data->num_of_philos);
	//  printf(RED"Total served = %ld\n"RESET, data->thr_running);
	// pthread_mutex_unlock(&data->print_mutex);
	while (!(data->end))
	{
		printf(RED"Monitoring philo \n"RESET);
		i = 0;
		while (i < data->num_of_philos)
		{
			if (ph_died(data->philo + i) == true)
			{
				print_message_mtx(data->philo, "is dead", RED);
				set_bool(&data->thr_running_mutex, &data->end, true);
				break ;
			}
			i++;
		}
		 pthread_mutex_lock(&data->print_mutex);
    	printf("Monitor exiting\n");
    	pthread_mutex_unlock(&data->print_mutex);
	}
	return (NULL);
}
