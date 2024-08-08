/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:49:24 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/08 12:43:45 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	main_struct;

	if (check(argc, argv) == 1)
		return (1);
	if (init_main(&main_struct, argc, argv) == 1)
	{
		printf("Failed to init main_struct");
		return (1);
	}
	main_struct.philo = malloc(main_struct.number_of_philo * sizeof(t_philo));
	main_struct.forks = malloc(main_struct.number_of_philo * sizeof(pthread_mutex_t));
	main_struct.threads = malloc((main_struct.number_of_philo + 1) * sizeof(pthread_t));
	if (init_philo(main_struct.philo, &main_struct) == 1)
	{
		printf("Failed to init philo struct");
		return (1);
	}
	if (init_threads(&main_struct) != 0)
	{
		printf("Failed to create threads");
		return (1);
	}
	if (join_threads(&main_struct) != 0)
	{
		printf("Failed to join threads");
		return (1);
	}
	destroy(&main_struct);
	free(main_struct.philo);
	free(main_struct.forks);
	free(main_struct.threads);
	return (0);
}
