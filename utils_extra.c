/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:47:59 by bposa             #+#    #+#             */
/*   Updated: 2024/08/12 01:42:49 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return(ERROR);
	return ((long long int)(time.tv_sec * 1000LL + time.tv_usec / 1000));
}

void	setter(void *var, int value, pthread_mutex_t *lock)
{
	if (lock && var)
	{
		pthread_mutex_lock(lock);
		*(int *)var = value;
		pthread_mutex_unlock(lock);
	}
	else
		printf("setter: ERROR with accessing mutex or struct's variable!\n");
}
