/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:07:27 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/09 14:07:35 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	order_of_forks(t_philo *philo)
{
	philo->right_fork = philo->index_philo - 1;
	philo->left_fork = philo->index_philo;
	if (philo->index_philo == philo->table->number_of_philo)
	{
		philo->right_fork = 0;
		philo->left_fork = philo->index_philo - 1;
	}
}

void	if_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->time_meal_lock);
	philo->table->next_meal = 1;
	pthread_mutex_unlock(&philo->table->time_meal_lock);
	ft_usleep(philo->table->next_meal, philo->table);
}

int	check_forks(t_philo *philo)
{
	if (read_finish_process(philo->table) >= philo->table->number_of_philo)
	{
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		return (1);
	}
	return (0);
}

void	update_all_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->time_meal_lock);
	philo->all_meal_eaten++;
	if (philo->all_meal_eaten == philo->table->must_eat)
		update_finish_process(philo->table, 1);
	pthread_mutex_unlock(&philo->table->time_meal_lock);
}

int	eat(t_philo *philo)
{
	order_of_forks(philo);
	if (philo->table->number_of_philo % 2 == 1)
		if_odd(philo);
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	if (read_finish_process(philo->table) >= philo->table->number_of_philo)
	{
		pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
		return (1);
	}
	protect_write(philo->table, philo->index_philo, "has taken a fork");
	if (philo->table->number_of_philo == 1)
		return (one_philo(philo));
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	if (check_forks(philo))
		return (1);
	protect_write(philo->table, philo->index_philo, "has taken a fork");
	if (check_forks(philo))
		return (1);
	protect_write(philo->table, philo->index_philo, "is eating");
	update_last_meal(philo, get_current_time());
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	update_all_meals_eaten(philo);
	return (0);
}
