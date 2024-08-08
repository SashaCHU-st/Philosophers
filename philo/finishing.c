/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finishing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:20:32 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/08 12:31:12 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_main *main_struct)
{
	int	j;

	j = 0;
	while (j < main_struct->creat_succesfull_threads)
	{
		if (pthread_join(main_struct->threads[j], NULL) != 0)
			return (1);
		j++;
	}
	return (0);
}

int	destroy(t_main *main_struct)
{
	int	i;

	i = 0;
	while (i < main_struct->number_of_philo)
	{
		if (pthread_mutex_destroy(main_struct->forks + i) != 0)
			return (1);
		i++;
	}
	return (0);
}
