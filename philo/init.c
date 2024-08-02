/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:27:25 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/02 15:29:04 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philo.h"

// int 	init_main(t_main *main, char **argv)
// {
// 	main->number_of_philo = ft_atol(argv[1]);
// 	main->time_to_die = ft_atol(argv[2]);
// 	main->time_to_eat = ft_atol(argv[3]);
// 	main->time_to_sleep = ft_atol(argv[4]);
// 	main->number_of_times_each_philo_must_eat = ft_atol(argv[5]);
// 	main->number_of_forks = ft_atol(argv[1]);
// 	main->start_time =  get_current_time();
// 	main->dead  = 0;
// 	main->all_ate = 0;
// 	if(pthread_mutex_init(&main->eat_lock, NULL) != 0)
// 		return(1);
// 	if(pthread_mutex_init(&main->meal_lock, NULL) != 0)
// 		return(1);
// 	if(pthread_mutex_init(&main->write_lock, NULL) != 0)
// 		return(1);
// 	return(0);
// }
// int	init_philo(t_philo *philo, t_main *main)
// {
// 	int	i;

// 	i = 0;
// 	while (i < main->number_of_philo)
// 	{
// 		philo[i].main = main;
// 		philo[i].index_philo = i + 1;
// 		philo[i].is_philo_ate = 0;
// 		philo[i].last_meal_time = get_current_time();
// 		philo[i].all_meal_eaten = 0;
// 		if(pthread_mutex_init(philo->right_fork, NULL) != 0)
// 			return(1);
// 		if(pthread_mutex_init(philo->left_fork, NULL) != 0)
// 			return(1);
// 		i++;
// 	}
// 	return(0);
// }