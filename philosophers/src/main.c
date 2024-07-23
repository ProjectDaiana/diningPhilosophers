/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:25:24 by darotche          #+#    #+#             */
/*   Updated: 2024/07/23 17:58:38 by darotche         ###   ########.fr       */
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
		//printf(RED"Philo id: %ld\n"RESET, philo->id);
		philo->full = false;
		philo->eat_count = 0;
		philo->data = data;
		// printf("philo->data->n_of_ph: %ld\n", philo->data->n_of_ph);
		// printf("philo->data->num_of_meals: %ld\n", philo->data->num_of_meals);
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

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_of_meals == 0)
		return ;
	if (data->n_of_ph == 1)
	{
		if (pthread_create(&data->philo[0].thr_id, NULL, &lone_ph_routine, &data->philo[0]))
		{
			printf("Error: Thread creation failed\n");
			exit (EXIT_FAILURE);
		}
	}
	else
	{
		while (i < data->n_of_ph)
		{
			if (pthread_create(&data->philo[i].thr_id, NULL, &routine, &data->philo[i]))
			{
				printf("Error: Thread creation failed\n");
				exit (EXIT_FAILURE);
			}
			i++;
		}
	}
	if (pthread_create(&data->monitor, NULL, &monitor, data))
	{
		printf("Error: Thread creation failed\n");
		exit (EXIT_FAILURE);
	}
	data->start_time = get_time();
	set_bool(&data->start_mutex, &data->start, true);
	//printf("All threads started\n");
}

void	data_init(t_data *data, char **argv)
{
	int	i;

	i = 0;
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
	while (i < data->n_of_ph)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		data->forks[i].id = i;
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->thr_running_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
	data->start_time = get_time();
	data->thr_running = 0;
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_ph)
	{
		pthread_join(data->philo[i].thr_id, NULL);
		//printf("Philo %ld joined\n", data->philo[i].id);
		i++;
	}
	set_bool(&data->thr_running_mutex, &data->end, true);
	pthread_join(data->monitor, NULL);
	//printf("All threads joined\n");
}

int	main(int argc, char **argv)
{
	static t_data	data;

	if (check_input(argc, argv))
		return (1);
	data_init(&data, argv);
	init_philo(&data);
	create_threads(&data);
	join_threads(&data);
	free_and_destroy(&data);
	return (0);
}
