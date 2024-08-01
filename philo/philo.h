/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:19:12 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/01 13:56:08 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
# include <sys/time.h>

typedef struct s_main
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep; 
	int	number_of_times_each_philo_must_eat;
	int	number_of_forks;
} t_main;

typedef struct s_philo
{
	int				index_philo;
	int				right_fork;
	pthread_mutex_t	left_fork;
	
} t_philo;


int	ft_isdigit(int arg);
int	ft_isspace(int arg);
long ft_atol(const char *str);
int check_arguments(char *argv);
int check(int argc, char **argv);
void init_main(t_main *main, char **argv);

#endif