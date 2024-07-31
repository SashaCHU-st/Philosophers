/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:49:24 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/29 13:29:10 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

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
	
	pthread_t t1, t2;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, &print1, NULL);
	pthread_create(&t2, NULL, print1, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", k);
	write(1, "exit\n", 5);
	return (0);
		
}