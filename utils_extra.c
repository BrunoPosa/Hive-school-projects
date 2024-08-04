/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:47:59 by bposa             #+#    #+#             */
/*   Updated: 2024/08/04 13:29:27 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return(ERROR);
	return ((long long int)(time.tv_sec * 1000LL + time.tv_usec / 1000));//(time.tv_usec + 500) / 1000??
}

void	edit_var(int	*var, int value, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*var = value;
	pthread_mutex_unlock(lock);
}

void	wait_until(int *var, int status, pthread_mutex_t *lock)
{
	while (1)
	{
		pthread_mutex_lock(lock);
		if (*var == status)
		{
			pthread_mutex_unlock(lock);
			break ;
		}
		pthread_mutex_unlock(lock);
		usleep(200);
	}
}
