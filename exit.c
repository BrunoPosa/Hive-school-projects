/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:39:06 by bposa             #+#    #+#             */
/*   Updated: 2024/08/07 12:43:23 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ermsg(int status)
{
	if (status == EVAL)
		write(2, "\nUsage\n        ./philo Philos T_die T_eat"
			" T_sleep [optional: Meals]\n\n", 69);
	if (status == EINIT)
		printf("\n\e[31mInitialization failed, please try again\e[0m\n\n");
	if (status == EARG)
		write(2, "\nMain arguments must be 1-9999\n", 31);
	if (status == EARGC)
		write(2, "\nMust have 4 or 5 arguments.\n", 29);
	if (status == ETHREAD)
		write(2, "\nThreads!\n", 10);
	if (status == EMALLOC)
		write(2, "\nMalloc!\n", 9);
	if (status == EMUTEX)
		write(2, "\nMutex!\n", 8);
	if (status == ERROR)
		write(2, "\nError!\n", 8);
	return (ERROR);
}

void free_philos(t_data *d)
{
    int i;

    i = -1;
    while (++i < d->n_philos)
    {
        if (d->philo[i])
        {
            free(d->philo[i]);
            d->philo[i] = NULL;
        }
    }
    free(d->philo);
    d->philo = NULL;
}

/*
	-Fix by protecting mutex_destroy() and pthread_join() [they ret 0 on success]!
	-Ditch i for sake of not doing free() inside return()
*/
int	cleanerr(t_data *d, int status, int initialized)
{
	if (status == EMUTEX || status == EMALLOC)
	{
		while (--initialized >= 0)
		{
			pthread_mutex_destroy(&d->forks[initialized]);
			if (d->philo[initialized])
				free(d->philo[initialized]);
		}
	}
	else if (status == ETHREAD)
	{
		setter(&d->death, DEATH, &d->dielock);
		while (--d->n_philos >= 0)
			pthread_mutex_destroy(&d->forks[d->n_philos]);
		while (--initialized >= 0)
			pthread_join(d->philo[initialized]->thread, NULL);
	}
	else
	{
		if (checker(d, MEAL) != SUCCESS)
			pthread_mutex_unlock(&d->printlock);
		while (--d->n_philos >= 0)
		{
			pthread_join(d->philo[d->n_philos]->thread, NULL);
			pthread_mutex_destroy(&d->forks[d->n_philos]);
		}
		pthread_mutex_destroy(&d->printlock);
	}
	free_philos(d);
	free(d);
// printf("\e[33mCleanerr done\e[0m\n");
	return (ermsg(status));
}
