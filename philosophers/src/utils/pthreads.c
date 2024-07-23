/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:06:25 by darotche          #+#    #+#             */
/*   Updated: 2024/07/23 21:07:13 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	s_pthr_create(pthread_t *thr_id, void *(*routine)(void *), void *arg)
{
	if (pthread_create(thr_id, NULL, routine, arg))
	{
		printf("Error: Thread creation failed\n");
		exit (EXIT_FAILURE);
	}
}

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_of_meals == 0)
		return ;
	if (data->n_of_ph == 1)
		s_pthr_create(&data->philo[0].thr_id, &lone_routine, &data->philo[0]);
	else
	{
		while (i < data->n_of_ph)
		{
			s_pthr_create(&data->philo[i].thr_id, &routine, &data->philo[i]);
			i++;
		}
	}
	s_pthr_create(&data->monitor, &monitor, data);
	data->start_time = get_time();
	set_bool(&data->start_mutex, &data->start, true);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_ph)
	{
		pthread_join(data->philo[i].thr_id, NULL);
		i++;
	}
	set_bool(&data->thr_run_mutex, &data->end, true);
	pthread_join(data->monitor, NULL);
}
