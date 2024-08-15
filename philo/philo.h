/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:19:12 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/15 08:38:01 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_main
{
	int				number_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				must_eat;
	long			start_time;
	int				finish_process;
	size_t			next_meal;
	pthread_mutex_t	*forks;
	struct s_philo	*philo;
	pthread_t		*threads;
	pthread_mutex_t	finish_process_lock;
	pthread_mutex_t	time_meal_lock;
	pthread_mutex_t	write_lock;
	int				creat_succesfull_threads;
}	t_main;

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