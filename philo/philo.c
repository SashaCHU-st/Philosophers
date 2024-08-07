/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:49:24 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/07 15:19:56 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	protect_write(philo->main_struct, philo->index_philo, "right has taken a fork");
	pthread_mutex_lock(&philo->main_struct->forks[second]);
	if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
	{
		pthread_mutex_unlock(&philo->main_struct->forks[first]);
		pthread_mutex_unlock(&philo->main_struct->forks[second]);
		return(1);
	}
	protect_write(philo->main_struct, philo->index_philo, "left has taken a fork");
	if (read_finish_process(philo->main_struct) >= philo->main_struct->number_of_philo)
	{
		pthread_mutex_unlock(&philo->main_struct->forks[first]);
		pthread_mutex_unlock(&philo->main_struct->forks[second]);
		return(1);
	}
	protect_write(philo->main_struct, philo->index_philo, "is eating");
	update_last_meal(philo, get_current_time());
	usleep(philo->main_struct->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->main_struct->forks[first]);
	pthread_mutex_unlock(&philo->main_struct->forks[second]);
	philo->all_meal_eaten++;
	if( philo->all_meal_eaten == philo->main_struct->number_of_times_each_philo_must_eat)
	{
		update_finish_process(philo->main_struct,1 );
	}
	return(0);
}

void *routine(void *arg)
{
	t_philo	*philo = (t_philo*)arg;

	if(philo->main_struct->number_of_philo == 1)
	{
		protect_write(philo->main_struct, philo->index_philo, "dead");
		update_finish_process(philo->main_struct,  philo->main_struct->number_of_philo);
	}
	else if(philo->index_philo % 2 == 1)
	{
		protect_write(philo->main_struct, philo->index_philo , "is thinking");
		usleep(10000);
	}
	while (read_finish_process(philo->main_struct) < philo->main_struct->number_of_philo)
	{
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


int starving(t_main *main_struct, int index_philo)
{
	pthread_mutex_lock(&main_struct->time_meal_lock);
	unsigned long current_time = get_current_time();
	if((current_time - main_struct->philo[index_philo].last_meal_time) >= main_struct->time_to_die)
	{
		pthread_mutex_unlock(&main_struct->time_meal_lock);
		protect_write(main_struct, index_philo + 1, "dead");
		update_finish_process(main_struct, main_struct->number_of_philo);
		return(1);
	}
	pthread_mutex_unlock(&main_struct->time_meal_lock);
	return(0);
}
int check_meal(t_main *main_struct)
{
	int i = 0;
	int all_philos_ate_enough = 1;

	//pthread_mutex_lock(&main_struct->time_meal_lock);
	while (i < main_struct->number_of_philo)
	{
		//printf("main_struct->philo[i].all_meal_eaten %d\n", main_struct->philo[i].all_meal_eaten);
		// printf("main_struct->number_of_times_each_philo_must_eat %d\n", main_struct->number_of_times_each_philo_must_eat);
		if(main_struct->is_infinite)
		{
			if (main_struct->philo[i].all_meal_eaten < main_struct->is_infinite)
			{
				all_philos_ate_enough = 0;
				//printf("1\n");
				break;
			}
			i++;
		}
		else
		{
			if (main_struct->philo[i].all_meal_eaten < main_struct->number_of_times_each_philo_must_eat)
			{
				all_philos_ate_enough = 0;
				//printf("2\n");
				break;
			}
			i++;
		}
	}
	// if (all_philos_ate_enough)
	// {
	// 	printf("HERE\n");
	// 	main_struct->finish_process = main_struct->number_of_philo;
	// }
	//pthread_mutex_unlock(&main_struct->time_meal_lock);
	return all_philos_ate_enough;
}

// int check_meal(t_main *main_struct)
// {
// 	printf("main_struct->finish_process %d\n",main_struct->finish_process);
// 	int i = 0;
// 	while(i < main_struct->number_of_philo)
// 	{
// 	pthread_mutex_lock(&main_struct->time_meal_lock);
// 		if(main_struct->philo[i].all_meal_eaten < main_struct->number_of_times_each_philo_must_eat)
// 		{
// 			pthread_mutex_lock(&main_struct->time_meal_lock);
// 			return(0);
// 		}
// 		main_struct->philo[i].all_meal_eaten = 1;
// 		pthread_mutex_unlock(&main_struct->time_meal_lock);
// 		i++;
// 	}
// 	pthread_mutex_lock(&main_struct->time_meal_lock);
// 	main_struct->finish_process = main_struct->number_of_philo;
// 	pthread_mutex_unlock(&main_struct->time_meal_lock);
// 	return(1);
// 	(void)main_struct;
// 	return(0);
// }

// void *monitor(void *arg)
// {
// 	t_main *main_struct = (t_main*)arg;
// 	int index_philo;
// 	while (read_finish_process(main_struct) < main_struct->number_of_philo)
// 	{
// 		index_philo = 0;
// 		while (index_philo < main_struct->number_of_philo)
// 		{
// 			//if (starving(main_struct, index_philo) || check_meal(main_struct))
// 			if (starving(main_struct, index_philo))
// 			{
// 				protect_write(main_struct, index_philo + 1, "dead");
// 				update_finish_process(main_struct, main_struct->number_of_philo);
// 				return(NULL);
// 			}
// 			index_philo++;
// 		}
// 		usleep(100);
// 	}
// 	return(NULL);
// }

void *monitor(void *arg)
{
	t_main *main_struct = (t_main*)arg;
	int index_philo;
	while (read_finish_process(main_struct) < main_struct->number_of_philo)
	{
		index_philo = 0;
		while (index_philo < main_struct->number_of_philo)
		{
			if (starving(main_struct, index_philo))
				return NULL;
			if(check_meal(main_struct))
				return(NULL);
			index_philo++;
		}
		// if (check_meal(main_struct))
		// {
		// 	// printf("main_struct->finish_process %d\n",main_struct->finish_process);
		// 	update_finish_process(main_struct, main_struct->number_of_philo);
		// 	return (NULL);
		// }
		usleep(1000);
	}
	return(NULL);
}

int	init_threads(t_main  *main_struct)
{
	int j = 0;
	main_struct->start_time =  get_current_time();
	while (j < main_struct->number_of_philo)
	{
		main_struct->philo[j].last_meal_time = get_current_time(); 
		if (pthread_create(&main_struct->threads[j], NULL, &routine, &main_struct->philo[j]) != 0)
				break ;
		j++;
	}
	main_struct->creat_succesfull_threads = j;
	if ((j == main_struct->number_of_philo) && pthread_create(&main_struct->threads[j], NULL, &monitor, main_struct) == 0)
		main_struct->creat_succesfull_threads++;
	if(main_struct->creat_succesfull_threads != (main_struct->number_of_philo + 1))
		update_finish_process(main_struct, main_struct->number_of_philo);
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

	if(check(argc, argv) == 1)
	{
		printf("Check the variable, can contain only numbers\n");
		return(1);
	}
	if(init_main(&main_struct, argc, argv) == 1)
	{
		printf("Failed to init main_struct");
		return(1);
	}
	main_struct.philo = malloc(main_struct.number_of_philo * sizeof(t_philo));
	main_struct.forks = malloc(main_struct.number_of_philo * sizeof(pthread_mutex_t));
	main_struct.threads = malloc((main_struct.number_of_philo + 1) * sizeof(pthread_t));
	if(init_philo(main_struct.philo, &main_struct) == 1)
	{
		printf("Failed to init philo struct");
		return(1);
	}
	if(init_threads(&main_struct) != 0)
	{
		printf("Failed to create threads");
		return(1);
	}
	if(join_threads(&main_struct) != 0)
	{
		printf("Failed to join threads");
		return(1);
	}
	destroy(&main_struct);
	free(main_struct.philo);
	free(main_struct.forks);
	free(main_struct.threads);
	return(0);
}