/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:39:43 by darotche          #+#    #+#             */
/*   Updated: 2024/07/22 19:50:54 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo, t_data *data)
{
	get_forks_mtx(philo);
	set_long(&philo->ph_mutex, &philo->last_eat_time, get_time());
	increase_long(&philo->ph_mutex, &philo->eat_count);
	//philo->eat_count++;
	print_message_mtx(philo, "is eating", YEL);
	usleep(data->time_to_eat * 1000);
	if (data->num_of_meals > 0 && philo->eat_count == data->num_of_meals)
	{
		set_bool(&philo->ph_mutex, &philo->full, true);
		//print_message_mtx(philo, "is full", RED);
	}
	// if (philo->id == 2)
	// 	philo->eat_count = 20;
	//printf(CYN"Ph %ld Eat count = %ld\n"RESET,philo->id, philo->eat_count);
	//set_long(&data->thr_running_mutex, &data->thr_running, data->thr_running + 1);
	//printf(CYN"Ph %ld Last eat time: %ld\n"RESET, philo->id, philo->last_eat_time);
	//printf(CYN"Ph %ld New eat count = %ld\n"RESET,philo->id, philo->eat_count);
	put_forks_mtx(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (!get_bool(&data->start_mutex, &data->start))// wait for all threads to start
		usleep(1000);
	set_long(&philo->ph_mutex, &philo->last_eat_time, get_time());// get time last meal
	increase_long(&data->thr_running_mutex, &data->thr_running); /// Increase the number of meals served
	while (!get_bool(&philo->data->thr_running_mutex, &philo->data->end))
	{
		if (get_bool(&philo->ph_mutex, &philo->full) && !get_bool(&philo->data->thr_running_mutex, &philo->data->end))
		{
            set_bool(&philo->ph_mutex, &philo->full, true);
			break ;
		}
		eat(philo, data);
		print_message_mtx(philo, "is sleeping", MAG);
		usleep(data->time_to_sleep * 1000);
		print_message_mtx(philo, "is thinking", MAG);
		usleep(2000);
	}
	return (NULL);
}

void	*lone_ph_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	// printf("time to die %ld\n", data->time_to_die);
	// printf("Num of philos %ld\n", data->n_of_ph);
	// printf("Num of meals %ld\n", data->num_of_meals);
	while (!get_bool(&data->start_mutex, &data->start))// wait for all threads to start
		usleep(1000);
	set_long(&philo->ph_mutex, &philo->last_eat_time, get_time());// get time last meal
	
	pthread_mutex_lock(&data->thr_running_mutex);
	data->thr_running++; /// Increase the number of meals served
	pthread_mutex_unlock(&data->thr_running_mutex);
	print_message_mtx(philo, "takes first fork", CYN);
	//printf("lone philo threads running %ld\n", data->thr_running);
	while (!data->end)
		usleep(1000);
	return (NULL);
}
