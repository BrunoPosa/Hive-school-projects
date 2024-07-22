/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:39:06 by bposa             #+#    #+#             */
/*   Updated: 2024/07/22 16:40:02 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int msg(int status)
{
	if (status == EVAL)
		write(2, "\nUsage:\n        ./philo Philos T_die T_eat"
			" T_sleep [optional: Meals]\n", 69);
	if (status == EINIT)
		write(2, "\nInitialization failed, please try again\n\n", 42);
	if (status == EARG)
		write(2, "\nEach argument must be 1-9999\n", 30);
	if (status == EARGC)
		write(2, "\nMust have 4 or 5 arguments.\n", 29);
	if (status == ETHREAD)
		write(2, "\nThreads!\n", 10);
	if (status == EMALLOC)
		write(2, "\nMalloc!\n", 9);
	if (status == EMUTEX)
		write(2, "\nMutex!\n", 8);
	return (ERROR);
}

int	cleanerr(t_data *d, int status, int initialized)
{
	int	i;

	i = -1;
	if (status == EMUTEX)
	{
		while (++i < initialized)
			pthread_mutex_destroy(&d->forks[i]);
	}
	else if (status == ETHREAD)
	{
		while (++i < d->n_philos)
			pthread_mutex_destroy(&d->forks[i]);
		i = -1;
		while (++i < initialized)
			pthread_join(d->philo[i].thread, NULL);
	}
	else
	{
		while (++i < d->n_philos)
		{
			pthread_mutex_destroy(&d->forks[i]);
			pthread_join(d->philo[i].thread, NULL);
		}
	}
	return (free(d), msg(status));
}
