/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finishing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:20:32 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/09 14:05:41 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_main *table)
{
	int	j;

	j = 0;
	while (j < table->creat_succesfull_threads)
	{
		if (pthread_join(table->threads[j], NULL) != 0)
			return (1);
		j++;
	}
	return (0);
}

int	destroy(t_main *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		if (pthread_mutex_destroy(table->forks + i) != 0)
			return (1);
		i++;
	}
	return (0);
}
