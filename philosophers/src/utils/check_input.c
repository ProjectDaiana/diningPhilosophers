/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darotche <darotche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 15:35:15 by darotche          #+#    #+#             */
/*   Updated: 2024/07/23 17:39:41 by darotche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
		{
			printf(RED "'%s' argument must be a number\n" RESET, str);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_for_alpha(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_all_digit(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf(RED "Wrong number of arguments\n"RESET);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (ft_atol(argv[1]) < 1 || ft_atol(argv[1]) > 200)
		{
			printf(RED"Number of philosophers must be between 1 and 200\n"RESET);
			exit (EXIT_FAILURE);
		}
		if (check_for_alpha(argc, argv))
			exit (EXIT_FAILURE);
	}
	if (ft_atol(argv[2]) < 60 || ft_atol(argv[3]) < 60 || ft_atol(argv[4]) < 60)
	{
		printf(RED"Time to die must be greater or equal than 60\n"RESET);
		exit (EXIT_FAILURE);
	}
	return (0);
}
