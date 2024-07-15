/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:25:24 by darotche          #+#    #+#             */
/*   Updated: 2024/07/15 18:01:32 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_t	create_philo(int philo_num, t_data *data)
{
	t_philo *philo = &data->philo[philo_num];
	philo->id = philo_num;
	philo->left_fork = philo_num;
	philo->right_fork = (philo_num + 1) % data->num_of_philos;
	philo->eat_count = 0;
	philo->last_eat_time = get_time();
	printf(RED"Last eat time: %ld\n" RESET, philo->last_eat_time);
	philo->data = data;

	if (pthread_create(&philo->thread_id, NULL, &routine, philo))
	{
		printf("Error: Thread creation failed\n");
		exit(1);
	}
	printf(BLU"Philosopher %d is created\n"RESET, philo->left_fork);
	printf(MAG"Philosopher left fork %d\n"RESET, philo->left_fork);
	printf(MAG"Philosopher right fork %d\n"RESET, philo->right_fork);	
	return (philo->thread_id); 
}

void	data_init(t_data *data, char **argv)
{
	int i;

	i = 0;
	data->num_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->total_meals = ft_atol(argv[5]);
	data->dead_philo = -1;
	data->total_served = 0;
	data->stop = false;
	data->philo = malloc(sizeof(t_philo) * data->num_of_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	//printf("Total meals: %ld\n", data->total_meals);
	if (!data->philo || !data->forks)
	{
		printf("Error: Memory allocation failed\n");
		exit(1);
	}
	i = 0;
	while(i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->total_served_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);

	data->start_time = get_time();
	data->start = true;
}

int main(int argc, char **argv)
{
	check_input(argc, argv);
	
	static t_data data;
	int i;

	data_init(&data, argv);
	pthread_t philo[data.num_of_philos];
	pthread_mutex_unlock(&data.start_mutex);
	//CREATE MONITOR
	if (pthread_create(&data.monitor, NULL, &monitor, &data))
	{
		printf("Error: Thread creation failed\n");
		exit(1);
	}
	///CREATE PHILOS
	i = 0;
	while (i < data.num_of_philos && data.start==true) 
	{
		pthread_mutex_lock(&data.start_mutex);
		philo[i] = create_philo(i, &data);
		i++;
	}
	pthread_mutex_unlock(&data.start_mutex);

	i = 0;
	//JOIN
	while(i < data.num_of_philos)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	pthread_join(data.monitor, NULL);
	
	//DESTROY
	i = 0;
	while(i < data.num_of_philos)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.total_served_mutex);
	pthread_mutex_destroy(&data.start_mutex);
	free(data.philo);
	free(data.forks);
	return (0);
}
