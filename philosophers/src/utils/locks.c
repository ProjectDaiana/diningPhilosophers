/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:29:09 by darotche          #+#    #+#             */
/*   Updated: 2024/07/23 20:06:49 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message_mtx(t_philo *philo, char *message)
{
	long	elapsed_time;

	if (get_bool(&philo->data->thr_running_mutex, &philo->data->end)== true)
		return ;
	elapsed_time = get_elapsed_time(philo->data->start_time);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %ld %s\n", elapsed_time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

// void	print_message_mtx(t_philo *philo, char *message, char *color)
// {
// 	long	elapsed_time;

// 	if (get_bool(&philo->data->thr_running_mutex, &philo->data->end)== true)
// 		return ;
// 	elapsed_time = get_elapsed_time(philo->data->start_time);
// 	pthread_mutex_lock(&philo->data->print_mutex);
// 	printf("%s%ld %ld %s\n"RESET, color, elapsed_time, philo->id, message);
// 	pthread_mutex_unlock(&philo->data->print_mutex);
// }

void	get_forks_mtx(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_message_mtx(philo, "has taken a fork");
	//print_message_mtx(philo, "has taken a fork", CYN);
	pthread_mutex_lock(&philo->right_fork->mutex);
	print_message_mtx(philo, "has taken a fork");
	//print_message_mtx(philo, "has taken a fork", CYN);
}

void	put_forks_mtx(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	//print_message_mtx(philo, "has left left fork", BLU);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	//print_message_mtx(philo, "has left right fork", BLU);
}
