/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:49:24 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/01 13:57:29 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_main(t_main *main, char **argv)
{
	main->number_of_philo = ft_atol(argv[1]);
	main->time_to_die = ft_atol(argv[2]);
	main->time_to_eat = ft_atol(argv[3]);
	main->time_to_sleep = ft_atol(argv[4]);
	main->number_of_times_each_philo_must_eat = ft_atol(argv[5]);
	main->number_of_forks = ft_atol(argv[1]) - 1;
}
void init_philo(t_philo *philo, t_main *main)
{
	int	i;

	i = 0;
	while (i < main->number_of_philo)
	{
		philo[i].index_philo = i + 1;
		philo[i].right_fork = 1;
		///philo[i].left_fork = phtread_mutex_init();
		
		i++;
	}
}
int main(int argc, char **argv)
{
	t_main	main;
	t_philo	*philo;
	
	if(check(argc, argv) == 1);
		printf("Not good\n");
	init_main(&main, argv);
	init_philo(&philo, &main);
	philo = malloc(sizeof(t_philo) * main.number_of_philo);
	
}