/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:49:24 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/04 13:56:20 by aheinane         ###   ########.fr       */
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
	while (i < argc)//argv[i])
	{
		if(check_arguments(argv[i]) == 1)
			return (1);
		// printf("{%d}\n", i);
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
int 	init_main(t_main *main_struct, int argc, char **argv)
{
	main_struct->number_of_philo = ft_atol(argv[1]);
	main_struct->time_to_die = ft_atol(argv[2]);
	main_struct->time_to_eat = ft_atol(argv[3]);
	main_struct->time_to_sleep = ft_atol(argv[4]);
	if (argc ==6)
	{
		main_struct->number_of_times_each_philo_must_eat = ft_atol(argv[5]);
		main_struct->is_infinite = 0;
	}
	else
	{
		main_struct->number_of_times_each_philo_must_eat = 0;
		main_struct->is_infinite = 1;
	}
	main_struct->number_of_forks = ft_atol(argv[1]);
	main_struct->start_time =  get_current_time();
	main_struct->finish_process = 0;
	if(pthread_mutex_init(&main_struct->finish_process_lock, NULL) != 0)
		return(1);
	if(pthread_mutex_init(&main_struct->time_meal_lock, NULL) != 0)
		return(1);
	if(pthread_mutex_init(&main_struct->write_lock, NULL) != 0)
		return(1);
	return(0);
}
int	init_philo(t_philo *philo, t_main *main_struct)
{
	int	i;
	
	i = 0;
	while (i < main_struct->number_of_philo)
	{
		if(pthread_mutex_init(main_struct->forks + i, NULL) != 0)
			return(1);
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
		// printf("init index {%d} the right_fork is {%d} left_fork is {%d}\n", i+1, philo->right_fork, philo->left_fork);
		// if (&main_struct->forks[philo->right_fork] == &main_struct->forks[philo->left_fork] )
		// 	printf("same fork\n");
		i++;
	}
	return(0);
}

unsigned long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error: gettimeofday\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// int	eat(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->main_struct->forks[philo->index_philo - 1]);
// 	protect_write(philo->main_struct, philo->index_philo, "has taken a fork");
// 	if (philo->index_philo != philo->main_struct->number_of_philo)
// 		pthread_mutex_lock(&philo->main_struct->forks[philo->index_philo + 1]);
// 	else
// 		pthread_mutex_lock(&philo->main_struct->forks[0]);
// 	protect_write(philo->main_struct, philo->index_philo, "has taken a fork");
// 	protect_write(philo->main_struct, philo->index_philo, "is eating");
// 	// ft_usleep(philo->main_struct->time_to_eat * 1000);
// 	usleep(philo->main_struct->time_to_eat * 1000);
// 	pthread_mutex_unlock(&philo->main_struct->forks[philo->index_philo - 1]);
// 	if (philo->index_philo != philo->main_struct->number_of_philo)
// 		pthread_mutex_unlock(&philo->main_struct->forks[philo->index_philo + 1]);
// 	else
// 		pthread_mutex_unlock(&philo->main_struct->forks[0]);
// 	philo->all_meal_eaten++;
// 	if( philo->all_meal_eaten == philo->main_struct->number_of_times_each_philo_must_eat)
// 		update_finish_process(philo->main_struct,1 );
// 	return(0);
// }

// int	eat_last(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->main_struct->forks[philo->index_philo - 1]);
// 	protect_write(philo->main_struct, philo->index_philo, "has taken a fork");
// 	if (philo->index_philo != philo->main_struct->number_of_philo)
// 		pthread_mutex_lock(&philo->main_struct->forks[philo->index_philo]);
// 	else
// 		pthread_mutex_lock(&philo->main_struct->forks[0]);
// 	protect_write(philo->main_struct, philo->index_philo, "has taken a fork");
// 	protect_write(philo->main_struct, philo->index_philo, "is eating");
// 	// ft_usleep(philo->main_struct->time_to_eat * 1000);
// 	usleep(philo->main_struct->time_to_eat * 1000);
// 	pthread_mutex_unlock(&philo->main_struct->forks[philo->index_philo - 1]);
// 	if (philo->index_philo != philo->main_struct->number_of_philo)
// 		pthread_mutex_unlock(&philo->main_struct->forks[philo->index_philo]);
// 	else
// 		pthread_mutex_unlock(&philo->main_struct->forks[0]);
// 	philo->all_meal_eaten++;
// 	if( philo->all_meal_eaten == philo->main_struct->number_of_times_each_philo_must_eat)
// 		update_finish_process(philo->main_struct,1 );
// 	return(0);
// }


int	eat(t_philo *philo)
{
	int	first;
	int second;
	first = philo->index_philo - 1;
	second = philo->index_philo;
	if (philo->index_philo == philo->main_struct->number_of_philo)
	{
		first = 0;
		second = philo->index_philo - 1;
	}
	pthread_mutex_lock(&philo->main_struct->forks[first]);
	if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
	{
		pthread_mutex_unlock(&philo->main_struct->forks[first]);
		return(1);
	}
	protect_write(philo->main_struct, philo->index_philo, "has taken a fork");
	pthread_mutex_lock(&philo->main_struct->forks[second]);
	if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
	{
		pthread_mutex_unlock(&philo->main_struct->forks[first]);
		pthread_mutex_unlock(&philo->main_struct->forks[second]);
		return(1);
	}
	protect_write(philo->main_struct, philo->index_philo, "has taken a fork");
	if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
	{
		pthread_mutex_unlock(&philo->main_struct->forks[first]);
		pthread_mutex_unlock(&philo->main_struct->forks[second]);
		return(1);
	}
	protect_write(philo->main_struct, philo->index_philo, "is eating");
	// ft_usleep(philo->main_struct->time_to_eat * 1000);
	usleep(philo->main_struct->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->main_struct->forks[first]);
	pthread_mutex_unlock(&philo->main_struct->forks[second]);
	philo->all_meal_eaten++;
	update_last_meal(philo, get_current_time());
	if( philo->all_meal_eaten == philo->main_struct->number_of_times_each_philo_must_eat)
	{
		// protect_write(philo->main_struct, philo->index_philo, "ate enoughl;kijkuhjyhgfhbjkml,;.lkiuytrgfthjkl,;.;");
		update_finish_process(philo->main_struct,1 );
	}
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
	ft_usleep(philo->main_struct->time_to_sleep *1000);
	return(0);
}

void *routine(void *arg)
{
	t_philo	*philo = (t_philo*)arg;
	// if (philo->main_struct->number_of_philo == philo->index_philo)
	// 	return (0);
	if(philo->index_philo % 2 == 1)
	{
		protect_write(philo->main_struct, philo->index_philo , "is thinking");
		usleep(10000);
	}
	while (read_finish_process(philo->main_struct) < philo->main_struct->number_of_philo)
	{
		// protect_write(philo->main_struct, philo->index_philo, "starting");
		if(eat(philo))
			return(NULL);
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
			return(0);
		protect_write(philo->main_struct, philo->index_philo, "is sleeping");
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
			return(0);
		usleep(philo->main_struct->time_to_sleep * 1000);
		if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
			return(0);
		protect_write(philo->main_struct, philo->index_philo, "is thinking");
	}
	return(NULL);
}

void *monitor(void *arg)
{
	t_main *main_struct = (t_main*)arg;
	int index_philo = 0;
	while (read_finish_process(main_struct) < main_struct->number_of_philo)
	{
		if ((main_struct->philo[index_philo].last_meal_time + main_struct->time_to_eat) <= get_current_time())
		{
			protect_write(main_struct, index_philo + 1, "dead");
			// main_struct->finish_process = main_struct->number_of_philo;
			update_finish_process(main_struct,  main_struct->number_of_philo);
		}
		index_philo++;
		if(main_struct->number_of_philo == index_philo)
			index_philo = 0;
		
	}
	return(NULL);
}
int	init_threads(t_main  *main_struct)
{
	int j = 0;
	main_struct->start_time =  get_current_time();
	while (j < main_struct->number_of_philo)
	{
		main_struct->philo[j].last_meal_time =get_current_time(); 
		if (pthread_create(&main_struct->threads[j], NULL, &routine, &main_struct->philo[j]) != 0)
				break ;
		j++;
	}
	main_struct->creat_succesfull_threads = j;
	if ((j == main_struct->number_of_philo) && pthread_create(&main_struct->threads[j], NULL, &monitor, main_struct) == 0)
		main_struct->creat_succesfull_threads++;
	if(main_struct->creat_succesfull_threads != (main_struct->number_of_philo + 1))
	{
		update_finish_process(main_struct, main_struct->number_of_philo);
		printf("fghg\n");
	}
	return(0);
}
int	join_threads(t_main  *main_struct)
{
	int j = 0;
	while (j < main_struct->creat_succesfull_threads)
	{
		if (pthread_join(main_struct->threads[j], NULL) != 0)
				return 1;
		j++;
	}
	return(0);
}
int destroy(t_main *main_struct)
{
		int	i;
	
	i = 0;
	while (i < main_struct->number_of_philo)
	{
		if(pthread_mutex_destroy(main_struct->forks + i) != 0)
			return(1);
		i++;
	}
	return(0);
}
int main(int argc, char **argv)
{
	t_main	main_struct;
	// t_philo	*philo;
	// pthread_mutex_t	*forks;
	if(check(argc, argv) == 1)
		printf("Not good\n");
	if(init_main(&main_struct, argc, argv) == 1)
		printf("NOT GOOD");
	main_struct.philo = malloc(main_struct.number_of_philo * sizeof(t_philo));
	main_struct.forks = malloc(main_struct.number_of_philo * sizeof(pthread_mutex_t));
	main_struct.threads = malloc((main_struct.number_of_philo + 1) * sizeof(pthread_t));
	if(init_philo(main_struct.philo, &main_struct) == 1)
		printf("NOT GOOODD");
	
	if(init_threads(&main_struct) != 0)
		printf("NOOOOT GOOOD");
	if(join_threads(&main_struct) != 0)
		printf("NOT GOOOD1");
	
	// int j = 0;
	// pthread_t th[j];
	// int thread_indices[main_struct.number_of_philo];
	// while (j < main_struct.number_of_philo)
	// {
	// 	if (pthread_create(&th[j], NULL, &routine, &thread_indices[j]) != 0)
	// 			return 1;
	// 	j++;
	// }
	// 	while (j < main_struct.number_of_philo)
	// {
	// 	if (pthread_join(th[j], NULL) != 0)
	// 		return 1;
	// 	j++;
	// }
	
	destroy(&main_struct);
	free(main_struct.philo);
	free(main_struct.forks);
	free(main_struct.threads);
}