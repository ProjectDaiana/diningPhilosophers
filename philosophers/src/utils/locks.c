/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:29:09 by darotche          #+#    #+#             */
/*   Updated: 2024/07/17 21:17:31 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message_mtx(t_philo *philo, char *message, char *color)
{
	long elapsed_time;

	elapsed_time = get_elapsed_time(philo->data->start_time);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%s%ld Philosopher %ld %s\n"RESET, color, elapsed_time, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	get_forks_mtx(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_message_mtx(philo, "has taken left fork", CYN);
	pthread_mutex_lock(&philo->right_fork->mutex);
	print_message_mtx(philo, "has taken right fork", CYN);
}

void	put_forks_mtx(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left_fork->mutex);
	print_message_mtx(philo, "has left left fork", BLU);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	print_message_mtx(philo, "has left right fork", BLU);
	print_message_mtx(philo, "has finished eating", GRN);
}