/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:19:52 by aheinane          #+#    #+#             */
/*   Updated: 2024/08/06 09:28:00 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// int	ft_usleep(size_t milliseconds)
// {
// 	size_t	start;

// 	start = get_current_time();
// 	while ((get_current_time() - start) < milliseconds)
// 		usleep(500);
// 	return (0);
// }

// unsigned long	get_current_time(void)
// {
// 	struct timeval	time;

// 	if (gettimeofday(&time, NULL) == -1)
// 		printf("Error: gettimeofday\n");
// 	return (time.tv_sec * 1000 + time.tv_usec / 1000);
// }