/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:19:12 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/01 12:03:23 by aheinane         ###   ########.fr       */
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
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep; 
	int				number_of_times_each_philosopher_must_eat;
} t_main;

typedef struct s_philo
{
	pthread_mutex_t	right_fork;
} t_philo;


int	ft_isdigit(int arg);
int	ft_isspace(int arg);
long ft_atol(const char *str);
int check_arguments(char *argv);
int check(int argc, char **argv);
void init_philo(t_main *main, char **argv);

#endif