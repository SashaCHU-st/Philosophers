#include "philo.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
# include <sys/time.h>

int k = 0;
pthread_mutex_t mutex;
void *print1(void *arg)
{
	int index = *(int*)arg;
	int i = 0;
	while(i < 10000 )
	{
		pthread_mutex_lock(&mutex);
		k++;
		//printf("k %d\n", k);
		pthread_mutex_unlock(&mutex);
	//	printf("I %d\n", k);
		i++;
	
	}
	return(NULL);
}
int main(int argc, char **argv)
{
	//srand(time(NULL));
	//int *res;
	int i;
	pthread_t th[4];
	//int how_many_threads[4];
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 4; i++)
	{
		//how_many_threads[i] = i;
		//if(pthread_create(&th[i], NULL, &print1, &how_many_threads[i]) != 0)
		if(pthread_create(&th[i], NULL, &print1, &i) != 0)
			return(1);///break ; 
		printf("thread ahs started %d\n", i);
	}
	// if(i < 4)
	// {
		for (int i = 0; i < 4; i++)
		{
			if(pthread_join(th[i], NULL) != 0)
				return(2);
			printf("thread ahs fnished %d\n", i);
		}
//	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", k);
	write(1, "exit\n", 5);
	return (0);
}