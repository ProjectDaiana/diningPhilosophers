/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:25:24 by darotche          #+#    #+#             */
/*   Updated: 2024/07/21 19:14:17 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{ 
	long i;
	t_philo *philo;

	i = 0;
	while (i < data->num_of_philos) 
	{
		philo = data->philo + i;
		philo->id = i + 1;
		printf(RED"Philo id: %ld\n"RESET, philo->id);
		philo->full = false;
		philo->eat_count = 0;
		philo->data = data;
		// printf("philo->data->num_of_philos: %ld\n", philo->data->num_of_philos);
		// printf("philo->data->num_of_meals: %ld\n", philo->data->num_of_meals);
		pthread_mutex_init(&philo->ph_mutex, NULL);
		
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
		philo->last_eat_time = get_time();
		i++;
	}
}


void	create_threads(t_data *data)
{
	int i;

	i = 0;
	// if (data->num_of_meals == 0)
	// 	return ;
	if (data->num_of_philos == 1)
	{
		if (pthread_create(&data->philo[0].thr_id, NULL, &lone_ph, &data->philo[0]))
		{
			printf("Error: Thread creation failed\n");
			exit(1);
		}
	}
	else {
		while (i < data->num_of_philos)
		{
			if (pthread_create(&data->philo[i].thr_id, NULL, &routine, &data->philo[i]))
			{
				printf("Error: Thread creation failed\n");
				exit(1);
			}
			i++;
		}
	}
	if (pthread_create(&data->monitor, NULL, &monitor, data))
	{
		printf("Error: Thread creation failed\n");
		exit(1);
	}
	data->start_time = get_time();
	set_bool(&data->start_mutex, &data->start, true); //All threads will start at the same time
	printf("All threads started\n");
}

void	data_init(t_data *data, char **argv)
{
	int i;

	i = 0;
	data->num_of_philos = ft_atol(argv[1]);
	printf("Num of philos: %ld\n", data->num_of_philos);
	data->time_to_die = ft_atol(argv[2]); //*1000 to convert to milliseconds
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if(data->time_to_die < 60 || data->time_to_eat < 60 || data->time_to_sleep < 60)
	{
		printf("Error: Time to die must be greater than 60\n");
		exit(1);
	}
	if(argv[5])
		data->num_of_meals = ft_atol(argv[5]);
	else
		data->num_of_meals = -1;
	data-> end = false;
	data->start = false;
	data->philo = safe_malloc(sizeof(t_philo) * data->num_of_philos);
	data->forks = safe_malloc(sizeof(t_forks) * data->num_of_philos);
	while(i < data->num_of_philos)
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
	//printf(data->num_of_meals == -1 ? "Number of meals: Unlimited\n" : "Number of meals: %ld\n", data->num_of_meals);
}


void	join_threads(t_data *data)
{
	int i;

	i = 0;
	while(i < data->num_of_philos)
	{
		pthread_join(data->philo[i].thr_id, NULL);
		printf("Philo %ld joined\n", data->philo[i].id);
		i++;
	}
	pthread_join(data->monitor, NULL);
	printf("All threads joined\n");
}	

int main(int argc, char **argv)
{
	check_input(argc, argv);
	 
	static t_data data;

	data_init(&data, argv);
	init_philo(&data);
	//printf(WHT"Data initialized\n"RESET);
	create_threads(&data);
	join_threads(&data);
	free_and_destroy(&data);

	return (0);
}
