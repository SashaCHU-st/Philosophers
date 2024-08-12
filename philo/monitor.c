/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:31:16 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/09 14:05:41 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	starving(t_main *table, int index_philo)
{
	unsigned long	current_time;

	pthread_mutex_lock(&table->time_meal_lock);
	current_time = get_current_time();
	if ((current_time - table->philo[index_philo].last_meal_time)
		>= table->time_to_die)
	{
		protect_write(table, index_philo + 1, "died");
		update_finish_process(table, table->number_of_philo);
		pthread_mutex_unlock(&table->time_meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->time_meal_lock);
	return (0);
}

void	*monitor(void *arg)
{
	t_main	*table;
	int		index_philo;

	table = (t_main *) arg;
	while (read_finish_process(table) < table->number_of_philo)
	{
		index_philo = 0;
		while (index_philo < table->number_of_philo)
		{
			if (starving(table, index_philo))
				return (NULL);
			index_philo++;
		}
		usleep(1000);
	}
	return (NULL);
}
