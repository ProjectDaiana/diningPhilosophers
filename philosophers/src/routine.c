/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:39:43 by darotche          #+#    #+#             */
/*   Updated: 2024/07/21 18:46:43 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo, t_data *data)
{
	get_forks_mtx(philo);
	set_long(&philo->ph_mutex, &philo->last_eat_time, get_time());
	philo->eat_count++;
	print_message_mtx(philo, "is eating", YEL);
	usleep(data->time_to_eat);
	if (data->num_of_meals > 0 && philo->eat_count == data->num_of_meals)
	{
		set_bool(&philo->ph_mutex, &philo->full, true);
		print_message_mtx(philo, "is full", RED);
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
	t_philo *philo;
	t_data *data;
	
	philo = (t_philo *)arg;
	data = philo->data;

	while (!get_bool(&data->start_mutex, &data->start))// wait for all threads to start
		;
	// printf(YEL"philo->data->num_of_philos: %ld\n"RESET, data->num_of_philos);
	// printf(YEL"philo->data->num_of_meals: %ld\n"RESET, data->num_of_meals);
	set_long(&philo->ph_mutex, &philo->last_eat_time, get_time());// get time last meal
	
	pthread_mutex_lock(&data->thr_running_mutex);
	data->thr_running++; /// Increase the number of meals served
	pthread_mutex_unlock(&data->thr_running_mutex);
	while (!data->end)
	{
		if (philo->full)
		{
			set_bool(&philo->ph_mutex, &philo->full, true);
			break ;
		}
		eat(philo, data);
		print_message_mtx(philo, "is sleeping", MAG);
		usleep(data->time_to_sleep * 1000);
	}
	return (NULL);
}

void	*lone_ph(void *arg)
{
	t_philo *philo;
	t_data *data;
	
	philo = (t_philo *)arg;
	data = philo->data;
	printf("time to die %ld\n", data->time_to_die);
	printf("Num of philos %ld\n", data->num_of_philos);
	printf("Num of meals %ld\n", data->num_of_meals);
	while (!get_bool(&data->start_mutex, &data->start))// wait for all threads to start
		;
	set_long(&philo->ph_mutex, &philo->last_eat_time, get_time());// get time last meal
	
	pthread_mutex_lock(&data->thr_running_mutex);
	data->thr_running++; /// Increase the number of meals served
	pthread_mutex_unlock(&data->thr_running_mutex);
	
	print_message_mtx(philo, "takes first fork", CYN);
	printf("lone philo threads running %ld\n", data->thr_running);
	while(!data->end)
		 ;
	return (NULL);
}