/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:49:24 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/02 17:51:26 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int arg)
{
	if (arg >= '0' && arg <= '9')
		return (1);
	else
		return (0);
}
int	ft_isspace(int arg)
{
	if ((arg >= 9 && arg <= 13) || arg == 32)
		return (1);
	else
		return (0);
}
long ft_atol(const char *str)
{
	long result = 0;
	int sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	check_arguments(char *argv)
{
	int	i;

	i = 0;
	if(ft_atol(argv) < 1)
	{
		printf("error???\n");
		return(1);
	}
	while (argv[i])
	{
		if(ft_isdigit(argv[i]) == 0)
			return(1);
		i++;
	}
	return (0);
}

int check(int argc, char **argv)
{
	int	i;

	i = 1;
	if(argc < 5 || argc > 6)
	{
		printf("error!!!!\n");
	}
	if(ft_atol(argv[1]) < 1)
	{
		printf("error,need at least 1 phil");
	}
	while (argv[i])
	{
		if(check_arguments(argv[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
int 	init_main(t_main *main, char **argv)
{
	main->number_of_philo = ft_atol(argv[1]);
	main->time_to_die = ft_atol(argv[2]);
	main->time_to_eat = ft_atol(argv[3]);
	main->time_to_sleep = ft_atol(argv[4]);
	main->number_of_times_each_philo_must_eat = ft_atol(argv[5]);
	main->number_of_forks = ft_atol(argv[1]);
	main->start_time =  get_current_time();
	main->all_ate = 0;
	main->dead_flag = 0;
	if(pthread_mutex_init(&main->eat_lock, NULL) != 0)
		return(1);
	if(pthread_mutex_init(&main->meal_lock, NULL) != 0)
		return(1);
	if(pthread_mutex_init(&main->write_lock, NULL) != 0)
		return(1);
	return(0);
}
int	init_philo(t_philo *philo, t_main *main)
{
	int	i;

	i = 0;
	while (i < main->number_of_philo)
	{
		philo[i].main = main;
		philo[i].index_philo = i + 1;
		philo[i].dead  = 0;
		philo[i].is_philo_ate = 0;
		philo[i].last_meal_time = get_current_time();
		philo[i].all_meal_eaten = 0;
		if(pthread_mutex_init(philo->right_fork, NULL) != 0)
			return(1);
		if(pthread_mutex_init(philo->left_fork, NULL) != 0)
			return(1);
		i++;
	}
	return(0);
}

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error: gettimeofday\n");
	return ((long long)time.tv_sec * 1000 + (long long)time.tv_usec / 1000);
}

int	eat(t_philo *philo)
{
	long start_time = get_current_time();
	long time = get_current_time() - start_time;
	pthread_mutex_lock(philo->right_fork);
	printf("%ld %d taken the right fork\n",time, philo->index_philo);
	pthread_mutex_lock(philo->left_fork);
	printf("%ld %d taken the left fork\n",time, philo->index_philo);
	ft_usleep(philo->main->time_to_eat * 1000);
	time = get_current_time() - start_time;
	printf("%ld %d eating \n",time, philo->index_philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return(0);
}

int	thinking(t_philo *philo)
{
	
	printf("%d thinking \n", philo->index_philo);
	return(0);
}

int	sleeping(t_philo *philo)
{
	printf("%d sleeping \n", philo->index_philo);
	ft_usleep(philo->main->time_to_sleep *1000);
	return(0);
}

void *routine(void *arg)
{
	t_philo	*philo = (t_philo*)arg;
	
	if(philo->index_philo % 2 == 1)
	{
		printf("thinking");
		usleep(philo->main->time_to_sleep * 500);
	}
	if(!philo->main->dead_flag)
	{
		if(eat(philo))
			return(NULL);
		if(thinking(philo))
			return(NULL);
		if(sleeping(philo))
			return(NULL);
	}
	return(NULL);
}

int main(int argc, char **argv)
{
	t_main	main;
	t_philo	*philo;
	
	if(check(argc, argv) == 1)
		printf("Not good\n");
	if(init_main(&main, argv) == 1)
		printf("NOT GOOD");
	philo = malloc(main.number_of_philo * sizeof(t_philo));
	if(init_philo(philo, &main) == 1)
		printf("NOT GOOODD");
	
	int j = 0;
	pthread_t th[j];
	int thread_indices[main.number_of_philo];
	while (j < main.number_of_philo)
	{
		if (pthread_create(&th[j], NULL, &routine, &thread_indices[j]) != 0)
				return 1;
		j++;
	}
		while (j < main.number_of_philo)
	{
		if (pthread_join(th[j], NULL) != 0)
			return 1;
		j++;
	}
	
}