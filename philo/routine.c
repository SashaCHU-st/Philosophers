/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:17:18 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/12 10:47:33 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_philo *philo)
{
	ft_usleep(philo->table->time_to_die, philo->table);
	pthread_mutex_lock(&philo->table->finish_process_lock);
	if (philo->table->finish_process < philo->table->number_of_philo)
	{
		protect_write(philo->table, philo->index_philo, "died");
		update_finish_process(philo->table, philo->table->number_of_philo);
	}
	pthread_mutex_unlock(&philo->table->finish_process_lock);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->table->write_lock);
	pthread_mutex_unlock(&philo->table->write_lock);
	if (philo->index_philo % 2 == 1)
	{
		protect_write(philo->table, philo->index_philo, "is thinking");
		ft_usleep(philo->table->time_to_eat, philo->table);
	}
	while (read_finish_process(philo->table) < philo->table->number_of_philo)
	{
		if (eat(philo))
			return (NULL);
		if (read_finish_process(philo->table) >= philo->table->number_of_philo)
			return (0);
		protect_write(philo->table, philo->index_philo, "is sleeping");
		if (read_finish_process(philo->table) >= philo->table->number_of_philo)
			return (0);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		if (read_finish_process(philo->table) >= philo->table->number_of_philo)
			return (0);
		protect_write(philo->table, philo->index_philo, "is thinking");
	}
	return (NULL);
}
