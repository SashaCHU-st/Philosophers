/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:19:12 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/02 17:08:30 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
# include <sys/time.h>

typedef struct s_main
{
	int				number_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep; 
	int				number_of_times_each_philo_must_eat;
	int				number_of_forks;
	long			start_time;
	int				all_ate;
	int				dead_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat_lock ;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	
} t_main;

typedef struct s_philo
{
	t_main			*main;
	int				*dead;
	int				index_philo;
	int				is_philo_ate;
	int				last_meal_time;
	int				all_meal_eaten;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	
} t_philo;


int			ft_isdigit(int arg);
int			ft_isspace(int arg);
long		ft_atol(const char *str);
int			check_arguments(char *argv);
int			check(int argc, char **argv);
int			init_main(t_main *main, char **argv);
int			init_philo(t_philo *philo, t_main *main);
long long	get_current_time(void);
int			eat(t_philo *philo);
void 		*routine(void *arg);
int			sleeping(t_philo *philo);
int			thinking(t_philo *philo);

#endif