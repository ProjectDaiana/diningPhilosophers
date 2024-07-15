/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:35:15 by darotche          #+#    #+#             */
/*   Updated: 2024/07/15 18:19:16 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_digit(char c)
{
	if(c >= '0' && c <= '9')
		return(1);
	return(0);
}

int is_all_digit(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(!is_digit(str[i]))
		{
			printf("Error: %s Argument must be a number\n", str);
			return(0);
		}
		i++;
	}
	return (1);
}

int check_input(int argc, char **argv)
{
	int i;

	i = 1;
	if(argc < 5 || argc > 6)
	{
		printf(RED "Error: Wrong number of arguments\n"RESET);
		exit(EXIT_FAILURE);
	}
	else
	{
		if(atoi(argv[1]) < 1)
		{
			printf(RED"Error: Number of philosophers must be greater than 0\n"RESET);
			exit(EXIT_FAILURE);
		}
		
		while (argv[i])
		{
			is_all_digit(argv[i]);	
			i++;
		}
	}
	return(0);	
}