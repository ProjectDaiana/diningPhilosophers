/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:39:43 by darotche          #+#    #+#             */
/*   Updated: 2024/07/17 20:05:39 by darotche         ###   ########.fr       */
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
		set_bool(&philo->ph_mutex, &philo->full, true);

	// if (philo->id == 2)
	// 	philo->eat_count = 20;
	//printf(CYN"Ph %ld Eat count = %ld\n"RESET,philo->id, philo->eat_count);
	//set_long(&data->total_served_mutex, &data->total_served, data->total_served + 1);
	//printf(CYN"Ph %ld Last eat time: %ld\n"RESET, philo->id, philo->last_eat_time);
	//printf(CYN"Ph %ld New eat count = %ld\n"RESET,philo->id, philo->eat_count);
	put_forks_mtx(philo);
}

void	is_dead(t_philo *philo)
{
	long current_time;

	current_time = get_time();
	if(current_time - philo->last_eat_time >= philo->data->time_to_die)
		philo->data->dead_philo = philo->id;
}

void	*routine(void *arg)
{
	t_philo *philo;
	t_data *data;
	
	philo = (t_philo *)arg;
	data = philo->data;
	while (!get_bool(&data->start_mutex, &data->start))
		;
	while (data->start)
	{
		if (philo->full)
			break ;
		is_dead(philo);
		eat(philo, data);
		print_message_mtx(philo, "is sleeping", MAG);
		usleep(data->time_to_sleep);
	}
	return (NULL);
}
