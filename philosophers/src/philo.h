
#ifndef PHILO_H
#define PHILO_H

#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define RESET "\033[0m"

#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/time.h>
#include <stdint.h>
#include <stdbool.h>

struct s_data;

typedef struct s_forks
{
	pthread_mutex_t	mutex;
	int				id;
} t_forks;

typedef struct s_philo
{
	int				id;
	long			eat_count;
	long 			last_eat_time;
	bool			full;
	t_forks			*left_fork;
	t_forks			*right_fork;
	pthread_t		thread_id;
	struct s_data	*data;
//	pthread_t		monitor;
//	t_forks			forks;
//	pthread_mutex_t	mutex;
} t_philo;

typedef struct s_data
{
	long			num_of_philos;
	unsigned long	time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			total_meals;
	long			total_served;
	int				dead_philo;
	bool			start;
	bool			stop;
	uint64_t		start_time;
	t_forks			*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t total_served_mutex;
	pthread_mutex_t start_mutex;
	pthread_t		monitor;
	t_philo			*philo;
} t_data;

int			check_input(int argc, char **argv);
void		*routine(void *arg);
void		*monitor(void *arg);

uint64_t	get_time(void);
uint64_t	get_elapsed_time(uint64_t start_time);

long		ft_atol(const char *str);

void		set_bool(pthread_mutex_t *mtx, bool *dest, bool val);
bool		get_bool(pthread_mutex_t *mtx, bool *val);
void		set_long(pthread_mutex_t *mtx, long *dest, long val);
long		get_long(pthread_mutex_t *mtx, long *val);

#endif