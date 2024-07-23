/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 20:46:44 by darotche          #+#    #+#             */
/*   Updated: 2024/07/23 21:06:56 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	long	i;
	t_philo	*philo;

	i = 0;
	while (i < data->n_of_ph) 
	{
		philo = data->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->eat_count = 0;
		philo->data = data;
		pthread_mutex_init(&philo->ph_mutex, NULL);
		if (philo->id % 2 == 0)
		{
			philo->left_fork = &data->forks[i];
			philo->right_fork = &data->forks[(i + 1) % data->n_of_ph];
		}
		else
		{
			philo->left_fork = &data->forks[(i + 1) % data->n_of_ph];
			philo->right_fork = &data->forks[i];
		}
		philo->last_eat_time = get_time();
		i++;
	}
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_ph)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		data->forks[i].id = i;
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->thr_run_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
}

void	data_init(t_data *data, char **argv)
{
	data->n_of_ph = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->end = false;
	data->start = false;
	data->philo = safe_malloc(sizeof(t_philo) * data->n_of_ph);
	data->forks = safe_malloc(sizeof(t_forks) * data->n_of_ph);
	if (argv[5])
		data->num_of_meals = ft_atol(argv[5]);
	else
		data->num_of_meals = -1;
	init_mutex(data);
	data->start_time = get_time();
	data->thr_run = 0;
}
