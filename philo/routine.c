/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:17:18 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/08 18:32:45 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->main_struct->write_lock);
	pthread_mutex_unlock(&philo->main_struct->write_lock);
	if (philo->index_philo % 2 == 1)
	{
		protect_write(philo->main_struct, philo->index_philo, "is thinking");
		ft_usleep(philo->main_struct->time_to_eat, philo->main_struct);
	}
	while (read_finish_process(philo->main_struct) < philo->main_struct->number_of_philo)
	{
		if (eat(philo))
			return (NULL);
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
			return (0);
		protect_write(philo->main_struct, philo->index_philo, "is sleeping");
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
			return (0);
		usleep(philo->main_struct->time_to_sleep * 1000);
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
			return (0);
		protect_write(philo->main_struct, philo->index_philo, "is thinking");
	}
	return (NULL);
}
