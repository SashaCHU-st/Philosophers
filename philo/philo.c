/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:49:24 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/15 08:38:31 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freeing_fun(t_main table)
{
	philo->number_of_philosophers = ft_atol(argv[1]);
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	philo->number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
}
void init_philo(t_philo *philo)
{
	///philo->right_fork = pthread_mutex_init();
	
}
int main(int argc, char **argv)
{
	t_main	main;
	t_philo	philo;
	
	if(check(argc, argv) == 1);
		printf("Not good\n");
	init_main(&main, argv);
	init_philo(&philo);
	
}