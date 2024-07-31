/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:19:12 by aheinane          #+#    #+#             */
/*   Updated: 2024/07/29 13:15:48 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

typedef struct s_philo
{
	pthread_mutex_t mutex;
	
} t_philo;

#endif