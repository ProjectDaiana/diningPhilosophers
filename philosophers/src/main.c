/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:25:24 by darotche          #+#    #+#             */
/*   Updated: 2024/07/16 16:39:59 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{ 
	long i;
	t_philo *philo;

	i = -1;
	while (++i < data->num_of_philos) 
	{
		philo = data->philo + i;
		philo->id = i + 1;
		printf(RED"Philo id: %ld\n"RESET, philo->id);
		philo->full = false;
		philo->eat_count = 0;
		philo->data = data;
		
		if (philo->id % 2 == 0)
		{
			philo->left_fork = &data->forks[i];
			philo->right_fork = &data->forks[(i + 1) % data->num_of_philos];
		}
		else
		{
			philo->left_fork = &data->forks[(i + 1) % data->num_of_philos];
			philo->right_fork = &data->forks[i];
		}
		//philo->last_eat_time = get_time();
	}
}

void	create_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philo[i].th_id, NULL, &routine, &data->philo[i]))
		{
			printf("Error: Thread creation failed\n");
			exit(1);
		}
		i++;
	}
	data->start_time = get_time();
	set_bool(&data->start_mutex, &data->start, true); //All threads will start at the same time
}

void	*safe_malloc(size_t size)
{
	void *ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		printf("Error: Memory allocation failed\n");
		exit(1);
	}
	return (ptr);
}

void	data_init(t_data *data, char **argv)
{
	int i;

	i = 0;
	data->num_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1000; //*1000 to convert to milliseconds
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if(data->time_to_die < 60000 || data->time_to_eat < 60000 || data->time_to_sleep < 60000)
	{
		printf("Error: Time to die must be greater than 60\n");
		exit(1);
	}
	if(argv[5])
		data->total_meals = ft_atol(argv[5]);
	else
		data->total_meals = -1;
	data->dead_philo = -1;
	data->total_served = 0;
	data->start = false;
	data->stop = false;
	data->philo = safe_malloc(sizeof(t_philo) * data->num_of_philos);
	data->forks = safe_malloc(sizeof(t_forks) * data->num_of_philos);
	//printf("Total meals: %ld\n", data->total_meals);

	while(i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks[i].mutex, NULL);
		data->forks[i].id = i;
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->total_served_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);

	data->start_time = get_time();
}

void	create_monitor(t_data *data)
{
	if (pthread_create(&data->monitor, NULL, &monitor, &data))
	{
		printf("Error: Thread creation failed\n");
		exit(1);
	}
}

void	join_threads(t_data *data)
{
	int i;

	i = 0;
	while(i < data->num_of_philos)
	{
		pthread_join(data->philo[i].th_id, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}	

void	destroy_mutex(t_data *data)
{
	int i;

	i = 0;
	while(i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i].mutex);
		i++;
	}
}

int main(int argc, char **argv)
{
	check_input(argc, argv);
	 
	static t_data data;

	data_init(&data, argv);
	init_philo(&data);

	create_monitor(&data);
	create_philos(&data);
	join_threads(&data);
	destroy_mutex(&data);
	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.total_served_mutex);
	pthread_mutex_destroy(&data.start_mutex);
	free(data.philo);
	free(data.forks);
	return (0);
}
