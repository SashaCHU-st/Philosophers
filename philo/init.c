/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:27:25 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/08 18:34:25 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_main *main_struct)
{
	int	j;

	j = 0;
	main_struct->start_time = get_current_time();
	pthread_mutex_lock(&main_struct->write_lock);
	while (j < main_struct->number_of_philo)
	{
		main_struct->philo[j].last_meal_time = get_current_time();
		if (pthread_create(&main_struct->threads[j], NULL,
				&routine, &main_struct->philo[j]) != 0)
			break ;
		j++;
	}
	pthread_mutex_unlock(&main_struct->write_lock);
	main_struct->creat_succesfull_threads = j;
	if ((j == main_struct->number_of_philo)
		&& pthread_create(&main_struct->threads[j], NULL,
			&monitor, main_struct) == 0)
		main_struct->creat_succesfull_threads++;
	if (main_struct->creat_succesfull_threads
		!= (main_struct->number_of_philo + 1))
		update_finish_process(main_struct, main_struct->number_of_philo);
	return (0);
}

int	init_main(t_main *main_struct, int argc, char **argv)
{
	main_struct->number_of_philo = ft_atol(argv[1]);
	main_struct->time_to_die = ft_atol(argv[2]);
	main_struct->time_to_eat = ft_atol(argv[3]);
	main_struct->time_to_sleep = ft_atol(argv[4]);
	main_struct->next_meal = 0;
	if (argc == 6)
	{
		main_struct->number_of_times_each_philo_must_eat = ft_atol(argv[5]);
		main_struct->is_infinite = 0;
	}
	else
	{
		main_struct->number_of_times_each_philo_must_eat = 0;
		main_struct->is_infinite = 1;
	}
	main_struct->start_time = get_current_time();
	main_struct->finish_process = 0;
	if (pthread_mutex_init(&main_struct->finish_process_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&main_struct->time_meal_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&main_struct->write_lock, NULL) != 0)
		return (1);
	return (0);
}

int	init_philo(t_philo *philo, t_main *main_struct)
{
	int	i;

	i = 0;
	while (i < main_struct->number_of_philo)
	{
		if (pthread_mutex_init(main_struct->forks + i, NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < main_struct->number_of_philo)
	{
		philo[i].main_struct = main_struct;
		philo[i].index_philo = i + 1;
		philo[i].last_meal_time = get_current_time();
		philo[i].all_meal_eaten = 0;
		philo->right_fork = i;
		philo->left_fork = (i + 1) % main_struct->number_of_philo;
		i++;
	}
	return (0);
}
