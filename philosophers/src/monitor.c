/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:26:09 by darotche          #+#    #+#             */
/*   Updated: 2024/07/23 16:18:50 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_thr_run(pthread_mutex_t	*mutex, long *threads, long n_of_ph)
{
	bool	ret;

	ret = false;
	//printf("Checking threads: %ld / %ld\n", threads, n_of_ph);
	pthread_mutex_lock(mutex);
	if (*threads == n_of_ph)
		ret = true;
	pthread_mutex_unlock(mutex);
	return (ret);
}

bool	ph_died(t_philo *philo)
{
	long	elapsed_time;
	long	ph_lastmeal_time;

	ph_lastmeal_time = get_long(&philo->ph_mutex, &philo->last_eat_time);
	elapsed_time = get_elapsed_time(ph_lastmeal_time);
	//	printf(RED"time %ld\n"RESET, elapsed_time);
	if (get_bool(&philo->ph_mutex, &philo->full))
		return (false);
	//printf(RED"Time since last eat: %ld\n"RESET, elapsed_time);
	//printf(RED "Time to die: %ld ms\n" RESET, philo->data->time_to_die);
	//pthread_mutex_lock(&philo->data->thr_running_mutex);
	if (elapsed_time > philo->data->time_to_die)
		return (true);
//	pthread_mutex_unlock(&philo->data->thr_running_mutex);
	return (false);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!all_thr_run(&data->thr_running_mutex, &data->thr_running, data->n_of_ph))
		usleep(1000);
	// pthread_mutex_lock(&data->print_mutex);
	// printf("Monitoring started\n");
	// pthread_mutex_unlock(&data->print_mutex);
	// pthread_mutex_lock(&data->print_mutex);
	//  printf("Checking threads: %ld / %ld\n", data->thr_running, data->n_of_ph);
	//  printf(RED"Total served = %ld\n"RESET, data->thr_running);
	// pthread_mutex_unlock(&data->print_mutex);
	
	//while (!data->end)
	while(get_bool(&data->end_mutex, &data->end) == false)
	{
		i = 0;
		while (i < data->n_of_ph && !get_bool(&data->end_mutex, &data->end))
		{
			if (ph_died(data->philo + i) == true)
			{
				set_bool(&data->end_mutex, &data->end, true);
				print_message_mtx(data->philo, "died", RED);
			//	exit (0);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
