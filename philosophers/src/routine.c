/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:39:43 by darotche          #+#    #+#             */
/*   Updated: 2024/07/16 17:57:20 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->total_served_mutex);
	if(!data->stop)
	{
		// pthread_mutex_lock(&data->forks[philo->left_fork]);
		// print_message_mtx(philo, "has taken a fork", YEL);
		// pthread_mutex_lock(&data->forks[philo->right_fork]);
		// print_message_mtx(philo, "has taken a fork", YEL);
		print_message_mtx(philo, "is eating", GRN);
				//usleep(data->time_to_eat);
		data->total_served++;
		philo->eat_count++;
		philo->last_eat_time = get_time();
		
		printf(GRN"Ph %ld Last eat time: %ld\n"RESET, philo->id, philo->last_eat_time);
		printf(GRN"Ph %ld New eat count = %ld\n"RESET,philo->id, philo->eat_count);
	}
	pthread_mutex_unlock(&data->total_served_mutex);
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
	while (!data->stop)
	{
		is_dead(philo);
		if (philo->full)
			break ;
		eat(philo, data);
		
		print_message_mtx(philo, "is sleeping", MAG);
		
		usleep(data->time_to_sleep * 1000);
	}
	return (NULL);
}

// void	*routine(void *arg)
// {
// 	t_data *data;
// 	t_philo *philo;
	
// 	data = philo->data;
// 	philo = (t_philo *)arg;

	
// 	usleep(100);//thinks for 1ms
// 	while (!data->stop)
// 	{
// 		is_dead(philo);
// 		if (philo->left_fork % 2 == 0)
// 		{
//             pthread_mutex_lock(&data->forks[philo->left_fork]);
// 			printf(YEL"%lu Philosopher %d got left fork. id=%lu\n", get_time(), philo->left_fork, philo->thread_id);
// 	        pthread_mutex_lock(&data->forks[philo->right_fork]);
// 			printf(YEL"%lu Philosopher %d got right fork. id=%lu\n", get_time(), philo->left_fork, philo->thread_id);
//         }
// 		else
// 		{
// 			pthread_mutex_lock(&data->forks[philo->right_fork]);
// 			printf(YEL"%lu Philosopher %d got right fork. id=%lu\n", get_time(), philo->left_fork, philo->thread_id);
// 			pthread_mutex_lock(&data->forks[philo->left_fork]);
// 			printf(YEL"%lu Philosopher %d got left fork. id=%lu\n", get_time(), philo->left_fork, philo->thread_id);
//         }
// 		eat(philo, philo->data);

// 		pthread_mutex_unlock(&data->forks[philo->left_fork]);
// 		pthread_mutex_unlock(&data->forks[philo->right_fork]);
// 		printf(MAG"%lu Philosopher %d is sleeping\n"RESET, get_time(), philo->left_fork);
// 		usleep(data->time_to_sleep * 1000);
		
// 		pthread_mutex_lock(&data->total_served_mutex);
// 		printf(GRN"Total served = %ld\n"RESET, data->total_served);
// 		pthread_mutex_unlock(&data->total_served_mutex);
// 	}
// 	// if(data->total_served == data->total_meals * data->num_of_philos)
// 	// {
// 	// 	printf("All philosophers have eaten %ld times\n", data->total_served);
// 	// 	exit(0);
// 	// }
// 	printf("Philosopher %d has eaten %ld times\n"RESET, philo->id, philo->eat_count);
// 	return (NULL);
// }
