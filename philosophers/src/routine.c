/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:39:43 by darotche          #+#    #+#             */
/*   Updated: 2024/07/11 20:44:45 by darotche         ###   ########.fr       */
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
	printf(GRN"%lu Philosopher %d " CYN"is eating, had %ld meals before.\n" RESET, get_time(), philo->left_fork, philo->eat_count);
	usleep(data->time_to_eat *1000);
	philo->eat_count++;
	data->total_served++;
	philo->last_eat_time = get_time();
	
	pthread_mutex_lock(&data->print_mutex);
	printf(GRN"Ph %d Last eat time: %ld\n"RESET, philo->left_fork, philo->last_eat_time);
	printf(GRN"Ph %d New eat count = %ld\n"RESET,philo->left_fork, philo->eat_count);
	pthread_mutex_unlock(&data->print_mutex);
}

void	is_dead(t_philo *philo)
{
	int64_t current_time;

	current_time = get_time();
	if(current_time - philo->last_eat_time >= philo->data->time_to_die)
		philo->data->dead_philo = philo->left_fork;
}

void	*routine(void *arg)
{
	//check if is 1 philo, odd or even
	t_philo *philo = (t_philo *)arg;
	t_data *data = philo->data;

	usleep(100);//thinks for 1ms
//	pthread_t th = pthread_self();
	//printf(RED"Philo %d has eatten %ld times before\n"RESET, philo->left_fork , philo->eat_count);
	while (data->dead_philo < 0 && data->total_served <= data->total_meals * data->num_of_philos)
	{
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
		/// mutex lock x2
		eat(philo, philo->data);
		// /mutex unlock x2
		usleep(data->time_to_sleep * 1000);
		//long long current_time = (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
		pthread_mutex_unlock(&data->forks[philo->left_fork]); //left fork 
		pthread_mutex_unlock(&data->forks[philo->right_fork]); //right fprk

		//pthread_mutex_lock(&data->print_mutex);
		printf("Philosopher %d finished eating\n\n"RESET, philo->left_fork);
		//pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_lock(&data->total_served_mutex);
		printf(GRN"Total served = %ld\n"RESET, data->total_served);
		pthread_mutex_unlock(&data->total_served_mutex);
		is_dead(philo);
	}
	printf("Philosopher %d has eaten %ld times\n"RESET, philo->id, philo->eat_count);
	return (NULL);
}
