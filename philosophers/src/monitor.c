/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:26:09 by darotche          #+#    #+#             */
/*   Updated: 2024/07/23 20:55:43 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_thr_run(pthread_mutex_t	*mutex, long *threads, long n_of_ph)
{
	bool	ret;

	ret = false;
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
	if (get_bool(&philo->ph_mutex, &philo->full))
		return (false);
	if (elapsed_time > philo->data->time_to_die)
		return (true);
	return (false);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!all_thr_run(&data->thr_run_mutex, &data->thr_run, data->n_of_ph))
		usleep(1000);
	while (!get_bool(&data->thr_run_mutex, &data->end))
	{
		i = 0;
		while (i < data->n_of_ph && !get_bool(&data->thr_run_mutex, &data->end))
		{
			if (ph_died(data->philo + i) == true)
			{
				print_message_mtx(data->philo, "died", RED);
				set_bool(&data->thr_run_mutex, &data->end, true);
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
