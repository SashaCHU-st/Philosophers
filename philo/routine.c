/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:17:18 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/06 13:27:00 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// int	eat(t_philo *philo)
// {
// 	int	first;
// 	int second;
// 	first = philo->index_philo - 1;
// 	second = philo->index_philo;
// 	if (philo->index_philo == philo->main_struct->number_of_philo)
// 	{
// 		first = 0;
// 		second = philo->index_philo - 1;
// 	}
// 	//update_last_meal(philo, get_current_time());
// 	pthread_mutex_lock(&philo->main_struct->forks[first]);
// 	if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
// 	{
// 		pthread_mutex_unlock(&philo->main_struct->forks[first]);
// 		return(1);
// 	}
// 	protect_write(philo->main_struct, philo->index_philo, "has taken a fork");
// 	pthread_mutex_lock(&philo->main_struct->forks[second]);
// 	if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
// 	{
// 		pthread_mutex_unlock(&philo->main_struct->forks[first]);
// 		pthread_mutex_unlock(&philo->main_struct->forks[second]);
// 		return(1);
// 	}
// 	protect_write(philo->main_struct, philo->index_philo, "has taken a fork");
// 	if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
// 	{
// 		pthread_mutex_unlock(&philo->main_struct->forks[first]);
// 		pthread_mutex_unlock(&philo->main_struct->forks[second]);
// 		return(1);
// 	}
// 	protect_write(philo->main_struct, philo->index_philo, "is eating");
// //	printf("Philosopher %d starts eating at time %lu\n", philo->index_philo, get_current_time());
// 	philo->last_meal_time = get_current_time();
// 	update_last_meal(philo, get_current_time());
// 	// ft_usleep(philo->main_struct->time_to_eat * 1000);
// 	usleep(philo->main_struct->time_to_eat * 1000);
// 	pthread_mutex_unlock(&philo->main_struct->forks[first]);
// 	pthread_mutex_unlock(&philo->main_struct->forks[second]);
// 	philo->all_meal_eaten++;
// 	if( philo->all_meal_eaten == philo->main_struct->number_of_times_each_philo_must_eat)
// 	{
// 		// protect_write(philo->main_struct, philo->index_philo, "ate enoughl;kijkuhjyhgfhbjkml,;.lkiuytrgfthjkl,;.;");
// 		update_finish_process(philo->main_struct,1 );
// 	}
// 	return(0);
// }

// void *routine(void *arg)
// {
// 	t_philo	*philo = (t_philo*)arg;

// 	if(philo->main_struct->number_of_philo == 1)
// 	{
// 		protect_write(philo->main_struct, philo->index_philo, "dead");
// 		update_finish_process(philo->main_struct,  philo->main_struct->number_of_philo);
// 	}
// 	else if(philo->index_philo % 2 == 1)
// 	{
// 		protect_write(philo->main_struct, philo->index_philo , "is thinking");
// 		usleep(10000);
// 	}
// 	while (read_finish_process(philo->main_struct) < philo->main_struct->number_of_philo)
// 	{
// 		if(eat(philo))
// 			return(NULL);
// 		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
// 			return(0);
// 		protect_write(philo->main_struct, philo->index_philo, "is sleeping");
// 		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
// 			return(0);
// 		usleep(philo->main_struct->time_to_sleep * 1000);
// 		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
// 			return(0);
// 		protect_write(philo->main_struct, philo->index_philo, "is thinking");
// 	}
// 	return(NULL);
// }