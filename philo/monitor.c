/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:31:16 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/08 17:07:12 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	starving(t_main *main_struct, int index_philo)
{
	unsigned long	current_time;

	pthread_mutex_lock(&main_struct->time_meal_lock);
	current_time = get_current_time();
	if ((current_time - main_struct->philo[index_philo].last_meal_time)
		>= main_struct->time_to_die)
	{
		protect_write(main_struct, index_philo + 1, "dead");
		update_finish_process(main_struct, main_struct->number_of_philo);
		pthread_mutex_unlock(&main_struct->time_meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&main_struct->time_meal_lock);
	return (0);
}

void	*monitor(void *arg)
{
	t_main	*main_struct;
	int		index_philo;

	main_struct = (t_main *) arg;
	while (read_finish_process(main_struct) < main_struct->number_of_philo)
	{
		index_philo = 0;
		while (index_philo < main_struct->number_of_philo)
		{
			if (starving(main_struct, index_philo))
				return (NULL);
			index_philo++;
		}
		usleep(1000);
	}
	return (NULL);
}
