/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:23:01 by darotche          #+#    #+#             */
/*   Updated: 2024/07/23 17:13:10 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RESET "\033[0m"

# include <pthread.h>
# include <stdio.h> 
# include <stdlib.h> 
# include <string.h> 
# include <unistd.h> 
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>

struct	s_data;

typedef struct s_forks
{
	pthread_mutex_t	mutex;
	int				id;
}	t_forks;

typedef struct s_philo
{
	long			id;
	long			eat_count;
	long			last_eat_time;
	bool			full;
	t_forks			*left_fork;
	t_forks			*right_fork;
	pthread_t		thr_id;
	pthread_mutex_t	ph_mutex;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	long			n_of_ph;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			num_of_meals;
	bool			end;
	bool			start;
	long			start_time;
	long			thr_running;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	thr_running_mutex;
	pthread_mutex_t	start_mutex;
	pthread_t		monitor;
	t_philo			*philo;
	t_forks			*forks;
}	t_data;

int			check_input(int argc, char **argv);
void		*routine(void *arg);
void		*lone_ph_routine(void *arg);
void		print_message_mtx(t_philo *philo, char *message, char *color);
long		ft_atol(const char *str);
void		*safe_malloc(size_t size);
void		get_forks_mtx(t_philo *philo);
void		put_forks_mtx(t_philo *philo);
void		*monitor(void *arg);
bool		all_thr_run(pthread_mutex_t	*mutex, long *threads, long n_of_ph);

long		get_time(void);
long		get_elapsed_time(long start_time);

void		set_bool(pthread_mutex_t *mtx, bool *dest, bool val);
bool		get_bool(pthread_mutex_t *mtx, bool *val);
void		set_long(pthread_mutex_t *mtx, long *dest, long val);
long		get_long(pthread_mutex_t *mtx, long *val);
void		increase_long(pthread_mutex_t *mutex, long *val);

bool	ph_died(t_philo *philo);

void		free_and_destroy(t_data *data);

#endif