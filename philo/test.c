#include "philo.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int k = 0;
pthread_mutex_t mutex;

void *print1(void *arg)
{
	int index = *(int*)arg;
	int i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&mutex);
		k++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return NULL;
	}

int main(int argc, char **argv)
{
	int i = atol(argv[1]);
	pthread_t th[i];
	int thread_indices[i];
		pthread_mutex_init(&mutex, NULL);

		for (int j = 0; j < i; j++)
		{
		thread_indices[j] = j;
		if (pthread_create(&th[j], NULL, &print1, &thread_indices[j]) != 0)
				return 1;
			printf("Thread has started %d\n", j);
		// for (int j = 0; j < i; j++)
		// {
		if (pthread_join(th[j], NULL) != 0)
				return 2;
			printf("Thread has finished %d\n", j);
	//	}
		}

		pthread_mutex_destroy(&mutex);
		printf("Number of increments: %d\n", k);
		write(1, "exit\n", 5);
		return 0;
}
