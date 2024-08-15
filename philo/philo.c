/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:49:24 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/15 08:45:18 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freeing_fun(t_main table)
{
	if (table.philo)
		free(table.philo);
	if (table.forks)
		free(table.forks);
	if (table.threads)
		free(table.threads);
}

int	error_msg(char *str)
{
	printf("%s", str);
	return (1);
}


int	check(int argc, char **argv)
{
	int	i;

	i = 2;
	if (argc < 5 || argc > 6)
	{
		printf("Wrong amount of arguments\n");
		return (1);
	}
	if (philo_num_check(argv))
		return (1);
	if (argc == 6 && ft_atol(argv[5]) < 1)
	{
		printf("invalid times each philo must eat\n");
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

int	main(int argc, char **argv)
{
	t_main	table;

	if (check(argc, argv) == 1)
		return (1);
	if (init_main(&table, argc, argv) == 1)
		error_msg("Failed to init table");
	table.philo = malloc(table.number_of_philo * sizeof(t_philo));
	if (!table.philo)
		freeing_fun(table);
	table.forks = malloc(table.number_of_philo * sizeof(pthread_mutex_t));
	if (!table.forks)
		freeing_fun(table);
	table.threads = malloc((table.number_of_philo + 1) * sizeof(pthread_t));
	if (!table.threads)
		freeing_fun(table);
	if (init_philo(table.philo, &table) == 1)
		error_msg("Failed to init philo struct");
	if (init_threads(&table) != 0)
		error_msg("Failed to init threads");
	if (join_threads(&table) != 0)
		error_msg("Failed to join threads");
	destroy(&table);
	freeing_fun(table);
	return (0);
}
