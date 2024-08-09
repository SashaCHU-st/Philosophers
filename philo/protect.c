/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:29:44 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/09 14:05:41 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	protect_write(t_main *table, int i, char *task)
{
	pthread_mutex_lock(&table->write_lock);
	printf("%lu %d %s\n", get_current_time() - table->start_time, i, task);
	pthread_mutex_unlock(&table->write_lock);
}

void	update_finish_process(t_main *table, int i)
{
	pthread_mutex_lock(&table->finish_process_lock);
	table->finish_process += i;
	pthread_mutex_unlock(&table->finish_process_lock);
}

int	read_finish_process(t_main *table)
{
	int	i;

	pthread_mutex_lock(&table->finish_process_lock);
	i = table->finish_process;
	pthread_mutex_unlock(&table->finish_process_lock);
	return (i);
}

void	update_last_meal(t_philo *philo, long long i)
{
	pthread_mutex_lock(&philo->table->time_meal_lock);
	philo->last_meal_time = i;
	pthread_mutex_unlock(&philo->table->time_meal_lock);
}

int	read_last_meal(t_philo *philo)
{
	long long	i;

	pthread_mutex_lock(&philo->table->time_meal_lock);
	i = philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->time_meal_lock);
	return (i);
}
