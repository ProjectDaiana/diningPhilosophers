/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:25:24 by darotche          #+#    #+#             */
/*   Updated: 2024/07/02 17:46:01 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t mutex;
	
// if time to die is reached
// if available get first fork
// if available get second fork 
// eat for time to eat
	// print message with timestamp
	// count eat
// sleep for time to sleep
// think for time to think
// repeat

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	//struct timeval tv;
	//gettimeofday(&tv, NULL);
	// printf("HUNGRY!!!\n");
	// printf(RED"Philo %d\n"RESET, philo->eat_count);
	// printf(RED"Meals = %d\n"RESET, philo.data->meals);
	while (philo->eat_count < philo->data->meals)
	{
		pthread_mutex_lock(&mutex);
		
		//pthread_t th = pthread_self();
		//philo->id = pthread_self();
		//printf(RED"!!!\n"RESET);
		printf("Philosopher %d is hungry\n", philo->left_fork);
		philo->eat_count++;
		
		//long long current_time = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
		//printf("%d Philosopher %d got left fork. id=%d\n", (int)time(NULL), philo->left_fork, philo->id);
		//printf("%d Philosopher %d got right fork. id=%d\n", (int)time(NULL), philo->right_fork, philo->id);
		//printf(YEL"%lld Philosopher %d is eating\n" RESET, current_time, philo->left_fork);
		//printf(GRN"Eat count = %d\n"RESET, philo->eat_count);
		pthread_mutex_unlock(&mutex);
		
		//printf(BLU"Philosopher %d is sleeping\n\n"RESET, philo->left_fork);
		usleep(500);
		//printf(CYN"Philosopher %d is thinking\n\n"RESET, philo->left_fork);
	}
	printf(BLU"Philosopher %d has eaten %d times\n"RESET, philo->left_fork, philo->eat_count);
	return (NULL);
}

pthread_t	create_philo(int philo_num, pthread_mutex_t *mutex, t_data *data)
{
	t_philo *philo = malloc(sizeof(t_philo));

	philo->left_fork = philo_num;
	philo->right_fork = (philo_num + 1) % 5;
	philo->eat_count = 0;
	philo->mutex = mutex;
	philo->data = data;

	printf(MAG"Philosopher %d is created\n"RESET, philo_num);
	printf("Philosopher %d has entered the room\n", philo_num);
		if (pthread_create(&philo->thread, NULL, &routine, data))
		{
			printf("Error: Thread creation failed\n");
			exit(1);
		} 
		printf("Philosopher %d has left the room\n", philo_num);
	return (philo->thread); 
}

int main(int argc, char **argv)
{
	static t_data data;
	int i;

	check_input(argc, argv);	
	data.meals = atoi(argv[2]);	
	data.num_of_philos = atoi(argv[1]);
	pthread_mutex_init(&mutex, NULL);
	
	pthread_t philo[data.num_of_philos];
	i = 0;
	while(i < data.num_of_philos)
	{
		philo[i] = create_philo(i, &mutex, &data);
		i++;
	}
	i =0;
	while(i < data.num_of_philos)
	{
		pthread_join(philo[i], NULL);
		i++;
	}	
	printf("All philosophers have eaten %d times\n", data.philo->eat_count);
  	pthread_mutex_destroy(&mutex);
	return (0);
}

// printf("%d %d has taken a fork",timestamp_in_ms, x);
// printf("%d %d is eating",timestamp_in_ms, x);
// printf("%d %d is sleeping",timestamp_in_ms, x);
// printf("%d %d is thinking",timestamp_in_ms, x);
// printf("%d %d died",timestamp_in_ms, x);