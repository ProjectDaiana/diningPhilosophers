/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:39:43 by darotche          #+#    #+#             */
/*   Updated: 2024/07/23 21:04:47 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo, t_data *data)
{
	get_forks_mtx(philo);
	set_long(&philo->ph_mutex, &philo->last_eat_time, get_time());
	increase_long(&philo->ph_mutex, &philo->eat_count);
	print_message_mtx(philo, "is eating", YEL);
	usleep(data->time_to_eat * 1000);
	if (data->num_of_meals > 0 && philo->eat_count == data->num_of_meals)
		set_bool(&philo->ph_mutex, &philo->full, true);
	put_forks_mtx(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!get_bool(&data->start_mutex, &data->start))
		usleep(1000);
	set_long(&philo->ph_mutex, &philo->last_eat_time, get_time());
	increase_long(&data->thr_run_mutex, &data->thr_run);
	while (!get_bool(&philo->data->thr_run_mutex, &philo->data->end))
	{
		if (get_bool(&philo->ph_mutex, &philo->full)
			&& !get_bool(&philo->data->thr_run_mutex, &philo->data->end))
		{
			set_bool(&philo->ph_mutex, &philo->full, true);
			break ;
		}
		eat(philo, data);
		print_message_mtx(philo, "is sleeping", MAG);
		usleep(data->time_to_sleep * 1000);
		print_message_mtx(philo, "is thinking", MAG);
		usleep(1000);
	}
	return (NULL);
}

void	*lone_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!get_bool(&data->start_mutex, &data->start))
		usleep(1000);
	set_long(&philo->ph_mutex, &philo->last_eat_time, get_time());
	increase_long(&data->thr_run_mutex, &data->thr_run);
	print_message_mtx(philo, "takes first fork", CYN);
	while (!get_bool(&data->thr_run_mutex, &data->end))
		usleep(1000);
	return (NULL);
}
