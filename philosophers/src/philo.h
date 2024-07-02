
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

typedef struct s_philo
{
	int id;
	int left_fork;
	int right_fork;
	int eat_count;
	pthread_t thread;
	pthread_mutex_t *mutex;
	t_data *data;
} t_philo;

typedef struct s_data
{
	int num_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int meals;
	pthread_mutex_t mutex;
	t_philo *philo;
} t_data;


int main(int argc, char **argv);
int check_input(int argc, char **argv);

#endif