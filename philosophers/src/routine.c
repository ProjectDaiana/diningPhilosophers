/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:39:43 by darotche          #+#    #+#             */
/*   Updated: 2024/07/15 17:32:48 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
	
// if time to die is reached
// if available get first fork
// if available get second fork 
// eat for time to eat
	// print message with timestamp
	// count eat
// sleep for time to sleep
// think for time to think
// repeat

// bool	is_dead(t_philo *philo)
// {
// 	struct timeval tv;
// 	long long current_time = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
// 	// if (current_time - philo->last_eat_time > philo->data->time_to_die)
// 	// { 
// 	// 	printf(RED"Philosopher %d is dead\n"RESET, philo->left_fork);
// 	// 	return (true);
// 	// }
// 	return (false);
// }


void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->total_served_mutex);
	if(!data->stop)
	{
		printf(GRN"%lu Philosopher %d " CYN"is eating, had %ld meals before.\n" RESET, get_time(), philo->left_fork, philo->eat_count);
		usleep(data->time_to_eat *1000);
		data->total_served++;
		philo->eat_count++;
		philo->last_eat_time = get_time();
		
		printf(GRN"Ph %d Last eat time: %ld\n"RESET, philo->left_fork, philo->last_eat_time);
		printf(GRN"Ph %d New eat count = %ld\n"RESET,philo->left_fork, philo->eat_count);
	}
	pthread_mutex_unlock(&data->total_served_mutex);
}

void	is_dead(t_philo *philo)
{
	uint64_t current_time;

	current_time = get_time();
	if(current_time - philo->last_eat_time >= philo->data->time_to_die)
		philo->data->dead_philo = philo->left_fork;
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_data *data;
	
	data = philo->data;
	usleep(100);//thinks for 1ms
	while (!data->stop)
	{
		is_dead(philo);
		if (philo->left_fork % 2 == 0)
		{
            pthread_mutex_lock(&data->forks[philo->left_fork]);
			printf(YEL"%lu Philosopher %d got left fork. id=%lu\n", get_time(), philo->left_fork, philo->thread_id);
	        pthread_mutex_lock(&data->forks[philo->right_fork]);
			printf(YEL"%lu Philosopher %d got right fork. id=%lu\n", get_time(), philo->left_fork, philo->thread_id);
        }
		else
		{
			pthread_mutex_lock(&data->forks[philo->right_fork]);
			printf(YEL"%lu Philosopher %d got right fork. id=%lu\n", get_time(), philo->left_fork, philo->thread_id);
			pthread_mutex_lock(&data->forks[philo->left_fork]);
			printf(YEL"%lu Philosopher %d got left fork. id=%lu\n", get_time(), philo->left_fork, philo->thread_id);
        }
		eat(philo, philo->data);

		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		printf(MAG"%lu Philosopher %d is sleeping\n"RESET, get_time(), philo->left_fork);
		usleep(data->time_to_sleep * 1000);
		
		pthread_mutex_lock(&data->total_served_mutex);
		printf(GRN"Total served = %ld\n"RESET, data->total_served);
		pthread_mutex_unlock(&data->total_served_mutex);
	}
	// if(data->total_served == data->total_meals * data->num_of_philos)
	// {
	// 	printf("All philosophers have eaten %ld times\n", data->total_served);
	// 	exit(0);
	// }
	printf("Philosopher %d has eaten %ld times\n"RESET, philo->id, philo->eat_count);
	return (NULL);
}
