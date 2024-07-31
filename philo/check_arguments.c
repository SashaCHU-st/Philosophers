/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:59:38 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/31 13:59:51 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arguments(char *argv)
{
	int	i;

	i = 0;
	printf("ft_atol(argv) %ld\n", ft_atol(argv));
	if(ft_atol(argv) < 1)
	{
		printf("error???\n");
		return(1);
	}
	while (argv[i])
	{
		if(ft_isdigit(argv[i]) == 0)
			return(1);
		i++;
	}
	return (0);
}

int check(int argc, char **argv)
{
	int	i;

	i = 1;
	if(argc < 5 || argc > 6)
	{
		printf("error!!!!\n");
	}
	if(ft_atol(argv[1]) < 1)
	{
		printf("error,need at least 1 phil");
	}
	while (argv[i])
	{
		if(check_arguments(argv[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}