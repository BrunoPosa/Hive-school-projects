/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:29:27 by bposa             #+#    #+#             */
/*   Updated: 2024/08/15 14:11:02 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ifonlyonefork(t_philo *p)
{
	if (!p->forktwo)
	{
		pthread_mutex_unlock(p->forkone);
		ft_usleep(p->die_t, p);
		setter(p->death, DEATH, p->dlock);
		return (DEATH);
	}
	return (ERROR);
}

void	swapforks(t_philo *p)
{
	pthread_mutex_t	*temp;

	temp = p->forkone;
	p->forkone = p->forktwo;
	p->forktwo = temp;
}

void	dropforks(t_philo *p)
{
	pthread_mutex_unlock(p->forkone);
	pthread_mutex_unlock(p->forktwo);
}

int	ft_usleep(long long int mseconds, t_philo *p)
{
	long long int	start;
	long long int	elapsed;

	start = get_time_ms();
	if (mseconds < 5)
		mseconds = 5;
	while (1)
	{
		if (getter(p->death, p->dlock))
			return (ERROR);
		elapsed = get_time_ms() - start;
		if (elapsed >= mseconds)
			break ;
		if (mseconds - elapsed > 1000)
			usleep(1000);
		else
			usleep((mseconds - elapsed) * 1000);
	}
	return (SUCCESS);
}

int	getter(int *var, pthread_mutex_t *lock)
{
	int	value;

	value = 0;
	if (!var || !lock)
		return (ERROR);
	pthread_mutex_lock(lock);
	value = *var;
	pthread_mutex_unlock(lock);
	return (value);
}
