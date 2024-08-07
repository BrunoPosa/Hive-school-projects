/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:33:44 by bposa             #+#    #+#             */
/*   Updated: 2024/08/07 18:30:52 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *d, int i)
{
	if (pthread_mutex_init(&d->philo[i]->dlock, NULL))
		return (cleanerr(d, ERROR, i));
	if (pthread_mutex_init(&d->philo[i]->golock, NULL))
	{
		pthread_mutex_destroy(&d->philo[i]->dlock);
		return (cleanerr(d, ERROR, i));
	}
	if (pthread_mutex_init(&d->philo[i]->readylock, NULL))
	{
		pthread_mutex_destroy(&d->philo[i]->dlock);
		pthread_mutex_destroy(&d->philo[i]->golock);
		return (cleanerr(d, ERROR, i));
	}
	if (pthread_mutex_init(&d->philo[i]->lmeallock, NULL))
	{
		pthread_mutex_destroy(&d->philo[i]->dlock);
		pthread_mutex_destroy(&d->philo[i]->golock);
		pthread_mutex_destroy(&d->philo[i]->readylock);
		return (cleanerr(d, ERROR, i));
	}
	return (SUCCESS);
}

int	init_philo(t_data *d, int i)
{
	d->philo[i] = malloc(sizeof(t_philo));
	if (!d->philo[i])
		return (ERROR);
	memset(d->philo[i], 0, sizeof(t_philo));
	d->philo[i]->id = i + 1;
	d->philo[i]->forkone = &d->forks[i];
	d->philo[i]->forktwo = &d->forks[(i + 1) % d->n_philos];
	if (d->n_philos == 1)
		d->philo[i]->forktwo = NULL;
	d->philo[i]->die_t = d->die_t;
	d->philo[i]->eat_t = d->eat_t;
	d->philo[i]->sleep_t = d->sleep_t;
	d->philo[i]->prlock = &d->printlock;
	d->philo[i]->start_t = &d->starttime;
	d->philo[i]->ready = -1;
	if (init_mutex(d, i) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

/*
	Forks (mutexes) start from 0
	Philos start from 0 + correspond to array index but their id is +1
	-Sometimes in isolated test w/ empty butler, the butler thread leaks (the detached one),
	but i suspect it will not when tested with all of the code uncommented.
	----CHECK MUTEX INIT FAILS, they need to be destroyed properly
*/
int	init_mu_th(t_data *d)
{
	int	i;

	i = -1;
	while (++i < d->n_philos)
	{
		if (pthread_mutex_init(&d->forks[i], NULL) != SUCCESS)
			return (cleanerr(d, EMUTEX, i));
	}
	if (pthread_mutex_init(&d->printlock, NULL))
		return (cleanerr(d, ERROR, i));
	if (pthread_mutex_init(&d->dielock, NULL))
		return (cleanerr(d, ERROR, i));
	i = -1;
	while (++i < d->n_philos)
	{
		if (init_philo(d, i) != SUCCESS)
			return (cleanerr(d, EMALLOC, i));
		if (pthread_create(&d->philo[i]->thread, NULL, (void *)&routine, d->philo[i])
			!= SUCCESS)
			return (cleanerr(d, ETHREAD, i));
	}
	if (pthread_create(&d->butler, NULL, (void *)&butler, d) != SUCCESS)
		return (cleanerr(d, ETHREAD, i));
	return (SUCCESS);
}

int	initor(char **argv, t_data *d)
{
	memset(d, 0, sizeof(t_data));
	d->n_philos = my_atoi(argv[1]);
	d->die_t = my_atoi(argv[2]);
	d->eat_t = my_atoi(argv[3]);
	d->sleep_t = my_atoi(argv[4]);
	if (argv[5])
		d->n_meals = my_atoi(argv[5]);
	else
		d->n_meals = ERROR;
	d->philo = malloc(d->n_philos * sizeof(t_philo *));
	if (!d->philo || !memset(d->philo, 0, d->n_philos * sizeof(t_philo *)))
	{
		free(d);
		return (ERROR);
	}
	d->forks = malloc(d->n_philos * sizeof(pthread_mutex_t));
	if (!d->forks || !memset(d->forks, 0, d->n_philos * sizeof(pthread_mutex_t)))
	{
		free(d->philo);
		free(d);
		return (ERROR);
	}
	if (init_mu_th(d) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
