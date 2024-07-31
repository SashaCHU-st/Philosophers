#include "philo.h"

int k = 0;
pthread_mutex_t mutex;
void *print1()
{
	int i = 0;
	while(i < 10000 )
	{
		pthread_mutex_lock(&mutex);
		k++;
		pthread_mutex_unlock(&mutex);
		i++;
	
	}
	return(NULL);
}
int main(int argc, char **argv)
{
	
	pthread_t th[4];
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 4; i ++)
	{
		pthread_create(&th[i], NULL, &print1, NULL);
			return(1);
		pthread_join(th[i], NULL);
			return(2);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", k);
	write(1, "exit\n", 5);
	return (0);
		
}