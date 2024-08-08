/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:07:27 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/08 18:34:49 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int one_philo(t_philo *philo)
{
		ft_usleep(philo->main_struct->time_to_die, philo->main_struct);
		pthread_mutex_lock(&philo->main_struct->finish_process_lock);
		if (philo->main_struct->finish_process < philo->main_struct->number_of_philo)
		{
			protect_write(philo->main_struct, philo->index_philo, "dead");
			update_finish_process(philo->main_struct, philo->main_struct->number_of_philo);
		}
		pthread_mutex_unlock(&philo->main_struct->finish_process_lock);
		return (1);
}

int	eat(t_philo *philo)
{
	//int	first;
	//int second;
	if( philo->main_struct->number_of_philo % 2 == 0)
	{
		philo->right_fork = philo->index_philo - 1;
		philo->left_fork = philo->index_philo;
		if (philo->index_philo == philo->main_struct->number_of_philo)
		{
			philo->right_fork = 0;
			philo->left_fork = philo->index_philo - 1;
		}
		pthread_mutex_lock(&philo->main_struct->forks[philo->right_fork]);
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
		{
			pthread_mutex_unlock(&philo->main_struct->forks[philo->right_fork]);
			return(1);
		}
		protect_write(philo->main_struct, philo->index_philo, "right has taken a fork");
		if (philo->main_struct->number_of_philo == 1)
			return(one_philo(philo));
		pthread_mutex_lock(&philo->main_struct->forks[philo->left_fork]);
		// update_fork_per_person(philo->main_struct, 1);
		// if(philo->forks_per_person != 2)
		// 	pthread_mutex_unlock(&philo->main_struct->forks[philo->right_fork]);
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
		{
			pthread_mutex_unlock(&philo->main_struct->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->main_struct->forks[philo->left_fork]);
			return(1);
		}
		protect_write(philo->main_struct, philo->index_philo, "left has taken a fork");
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
		{
			pthread_mutex_unlock(&philo->main_struct->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->main_struct->forks[philo->left_fork]);
			return(1);
		}
		protect_write(philo->main_struct, philo->index_philo, "is eating");
		update_last_meal(philo, get_current_time());
		ft_usleep(philo->main_struct->time_to_eat, philo->main_struct);
		pthread_mutex_unlock(&philo->main_struct->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->main_struct->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->main_struct->time_meal_lock);
		philo->all_meal_eaten++;
		if( philo->all_meal_eaten == philo->main_struct->number_of_times_each_philo_must_eat)
			update_finish_process(philo->main_struct,1 );
		pthread_mutex_unlock(&philo->main_struct->time_meal_lock);
		return(0);
	}
	else
	{
		philo->right_fork = philo->index_philo - 1;
		philo->left_fork = philo->index_philo;
		if (philo->index_philo == philo->main_struct->number_of_philo)
		{
			philo->right_fork = 0;
			philo->left_fork = philo->index_philo - 1;
		}
		pthread_mutex_lock(&philo->main_struct->time_meal_lock);
		philo->main_struct->next_meal = 1;
		pthread_mutex_unlock(&philo->main_struct->time_meal_lock);
		// if( philo->main_struct->number_of_philo % 2 == 0)
		ft_usleep(philo->main_struct->next_meal, philo->main_struct);
		pthread_mutex_lock(&philo->main_struct->forks[philo->right_fork]);
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
		{
			pthread_mutex_unlock(&philo->main_struct->forks[philo->right_fork]);
			return(1);
		}
		protect_write(philo->main_struct, philo->index_philo, "right has taken a fork");
		if (philo->main_struct->number_of_philo == 1)
			return(one_philo(philo));
		pthread_mutex_lock(&philo->main_struct->forks[philo->left_fork]);
		// update_fork_per_person(philo->main_struct, 1);
		// if(philo->forks_per_person != 2)
		// 	pthread_mutex_unlock(&philo->main_struct->forks[philo->right_fork]);
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
		{
			pthread_mutex_unlock(&philo->main_struct->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->main_struct->forks[philo->left_fork]);
			return(1);
		}
		protect_write(philo->main_struct, philo->index_philo, "left has taken a fork");
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
		{
			pthread_mutex_unlock(&philo->main_struct->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->main_struct->forks[philo->left_fork]);
			return(1);
		}
		protect_write(philo->main_struct, philo->index_philo, "is eating");
		update_last_meal(philo, get_current_time());
		ft_usleep(philo->main_struct->time_to_eat, philo->main_struct);
		pthread_mutex_unlock(&philo->main_struct->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->main_struct->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->main_struct->time_meal_lock);
		philo->all_meal_eaten++;
		if( philo->all_meal_eaten == philo->main_struct->number_of_times_each_philo_must_eat)
			update_finish_process(philo->main_struct,1 );
		pthread_mutex_unlock(&philo->main_struct->time_meal_lock);
		return(0);
	}
	return(0);
}