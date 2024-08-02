#include "philo.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

int k = 0;
pthread_mutex_t mutex;

long long	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error: gettimeofday\n");
	return ((long long)time.tv_sec * 1000 + (long long)time.tv_usec / 1000);
}
void *print1(void *arg)
{
	int index = *(int*)arg;
	int i = 0;
	long start_time = get_current_time();
	long time = get_current_time() - start_time;
	while (i < 5)
	{
		pthread_mutex_lock(&mutex);
		printf("%ld %d taken the right fork\n",time, k);
		printf("%ld %d taken the left fork\n",time, k);
		k++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return NULL;
	}

int main(int argc, char **argv)
{
	t_main main;
	int i = atol(argv[1]);
	pthread_t th[i];
	int thread_indices[i];
		pthread_mutex_init(&mutex, NULL);
		for (int j = 0; j < i; j++)
		{
		thread_indices[j] = j;
		if (pthread_create(&th[j], NULL, &print1, &thread_indices[j]) != 0)
				return 1;
		//printf("Thread has started %d\n", j);
		// for (int j = 0; j < i; j++)
		// {
		//printf("Thread has finished %d\n", j);
	//	}
		}
		if (pthread_join(th[j], NULL) != 0)
				return 2;
		pthread_mutex_destroy(&mutex);
		write(1, "exit\n", 5);
		return 0;
}
// #include "philo.h"
// #include <unistd.h>
// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/time.h>

// int k = 0;
// pthread_mutex_t mutex;

// void *print1(void *arg)
// {
// 	int j = *(int*)arg;
// 	int i = 0;
// 	while (i < j)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		k++;
// 		pthread_mutex_unlock(&mutex);
// 		i++;
// 	}
// 	return NULL;
// }

// int main(int argc, char **argv)
// {
// 	int i = atol(argv[1]);
// 	pthread_t th[i];
// 	int thread_indices[i];
// 		pthread_mutex_init(&mutex, NULL);

// 		for (int j = 0; j < i; j++)
// 		{
// 		thread_indices[j] = j;
// 		if (pthread_create(&th[j], NULL, print1, &thread_indices[j]) != 0)
// 				return 1;
// 		printf("%d is thinking\n", j);
// 		// for (int j = 0; j < i; j++)
// 		// {
// 		if (pthread_join(th[j], NULL) != 0)
// 				return 2;
// 			printf("Thread has finished %d\n", j);
// 	//	}
// 		}

// 		pthread_mutex_destroy(&mutex);
// 		printf("Number of increments: %d\n", k);
// 		write(1, "exit\n", 5);
// 		return 0;
// }