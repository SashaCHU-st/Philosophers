/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:27:25 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/12 16:22:00 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_main *table)
{
	int	j;

	j = 0;
	table->start_time = get_current_time();
	pthread_mutex_lock(&table->write_lock);
	while (j < table->number_of_philo)
	{
		table->philo[j].last_meal_time = get_current_time();
		if (pthread_create(&table->threads[j], NULL,
				&routine, &table->philo[j]) != 0)
			break ;
		j++;
	}
	pthread_mutex_unlock(&table->write_lock);
	table->creat_succesfull_threads = j;
	if ((j == table->number_of_philo)
		&& pthread_create(&table->threads[j], NULL,
			&monitor, table) == 0)
		table->creat_succesfull_threads++;
	if (table->creat_succesfull_threads
		!= (table->number_of_philo + 1))
		update_finish_process(table, table->number_of_philo);
	return (0);
}

int	init_main(t_main *table, int argc, char **argv)
{
	table->number_of_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->next_meal = 0;
	if (argc == 6)
		table->must_eat = ft_atol(argv[5]);
	table->start_time = get_current_time();
	table->finish_process = 0;
	if (pthread_mutex_init(&table->finish_process_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->time_meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->finish_process_lock);
		return (1);
	}
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->finish_process_lock);
		pthread_mutex_destroy(&table->time_meal_lock);
		return (1);
	}
	return (0);
}

void	if_failed_init_forks(t_main *table)
{
	pthread_mutex_destroy(&table->finish_process_lock);
	pthread_mutex_destroy(&table->time_meal_lock);
	pthread_mutex_destroy(&table->write_lock);
}

int	init_philo(t_philo *philo, t_main *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		if (pthread_mutex_init(table->forks + i, NULL) != 0)
		{
			if_failed_init_forks(table);
			freeing_fun(table);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < table->number_of_philo)
	{
		philo[i].table = table;
		philo[i].index_philo = i + 1;
		philo[i].last_meal_time = get_current_time();
		philo[i].all_meal_eaten = 0;
		philo->right_fork = i;
		philo->left_fork = (i + 1) % table->number_of_philo;
		i++;
	}
	return (0);
}
