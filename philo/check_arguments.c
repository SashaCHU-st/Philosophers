/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:59:38 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/12 14:09:36 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int arg)
{
	if (arg >= '0' && arg <= '9')
		return (1);
	else
		return (0);
}

int	ft_isspace(int arg)
{
	if ((arg >= 9 && arg <= 13) || arg == 32)
		return (1);
	else
		return (0);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	check_arguments(char *argv, int argc)
{
	int	i;

	i = 0;
	if (ft_atol(argv) < 1)
	{
		printf("no negative timing\n");
		return (1);
	}
	if (argc == 6 && ft_atol(&argv[5]) < 1)
	{
		printf("invalid times each philo must eat\n");
		return (1);
	}
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0)
		{
			printf("Check the variable, can contain only numbers\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Wrong amount of arguments\n");
		return (1);
	}
	if (ft_atol(argv[1]) < 1)
	{
		printf("Error,need at least 1 philo\n");
		return (1);
	}
	while (i < argc)
	{
		if (check_arguments(argv[i], argc) == 1)
			return (1);
		i++;
	}
	return (0);
}
