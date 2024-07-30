/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:29:27 by bposa             #+#    #+#             */
/*   Updated: 2024/07/30 14:47:07 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_atoi(char *n)
{
	int	res;

	res = 0;
	while (n && *n >= '0' && *n <= '9')
		res = res * 10 + *n++ - '0';
	return (res);
}

void	printer(int arg, char *str, t_philo *p)
{
	if (!*p->dead)
	{
		pthread_mutex_lock(p->prlock);
		printf("%lld %d %s\n", get_time_ms() - *p->start_t, arg, str);
		pthread_mutex_unlock(p->prlock);
	}
}


long long int	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return(ERROR);
	return ((long long int)(time.tv_sec * 1000LL + time.tv_usec / 1000));//(time.tv_usec + 500) / 1000??
}

int	wait_ms(long long int mseconds, t_philo *p)
{
	long long int	start;
	long long int	current;

	current = 0;
	start = get_time_ms();
	while (!*p->dead && current - start < mseconds)
	{
		current = get_time_ms();
		usleep(400);
	}
	return (SUCCESS);
}
