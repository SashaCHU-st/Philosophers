/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:29:44 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/06 14:51:34 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	protect_write(t_main *main_struct, int i, char *task)
{
	pthread_mutex_lock(&main_struct->write_lock);
	printf("%lu %d %s\n", get_current_time() - main_struct->start_time, i, task);
	//printf("%lu %d %s\n", get_current_time() - main_struct->philo->last_meal_time, i, "last time eat");
	pthread_mutex_unlock(&main_struct->write_lock);
}

void	update_finish_process(t_main *main_struct, int i)
{
	pthread_mutex_lock(&main_struct->finish_process_lock);
	main_struct->finish_process += i;
	pthread_mutex_unlock(&main_struct->finish_process_lock);
}

int	read_finish_process(t_main *main_struct)
{
	int	i;
	//printf("main_struct->finish_process %d\n", main_struct->finish_process );
	pthread_mutex_lock(&main_struct->finish_process_lock);
	i = main_struct->finish_process;
	pthread_mutex_unlock(&main_struct->finish_process_lock);
	return(i);
}

void	update_last_meal(t_philo *philo, long long i)
{
	pthread_mutex_lock(&philo->main_struct->time_meal_lock);
	philo->last_meal_time = i;
	pthread_mutex_unlock(&philo->main_struct->time_meal_lock);
}

int	read_last_meal(t_philo *philo)
{
	long long	i;

	pthread_mutex_lock(&philo->main_struct->time_meal_lock);
	i = philo->last_meal_time;
	pthread_mutex_unlock(&philo->main_struct->time_meal_lock);
	return(i);
}