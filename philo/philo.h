/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:19:12 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/12 14:09:53 by aheinane         ###   ########.fr       */
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
	t_main			*table;
	int				index_philo;
	unsigned long	last_meal_time;
	int				all_meal_eaten;
	int				right_fork;
	int				left_fork;
}	t_philo;
int				ft_isdigit(int arg);
int				ft_isspace(int arg);
long			ft_atol(const char *str);
int				check_arguments(char *argv, int argc);
int				check(int argc, char **argv);
int				init_main(t_main *table, int argc, char **argv);
int				init_philo(t_philo *philo, t_main *main);
int				init_threads(t_main *table);
unsigned long	get_current_time(void);
int				eat(t_philo *philo);
void			*routine(void *arg);
void			protect_write(t_main *main, int i, char *task);
void			update_finish_process(t_main *main, int i);
int				read_finish_process(t_main *main);
void			update_last_meal(t_philo *philo, long long i);
int				read_last_meal(t_philo *philo);
int				starving(t_main *table, int index_philo);
void			*monitor(void *arg);
int				ft_usleep(size_t milliseconds, t_main *table);
int				destroy(t_main *table);
int				join_threads(t_main *table);
int				one_philo(t_philo *philo);

#endif