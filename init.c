/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:33:44 by bposa             #+#    #+#             */
/*   Updated: 2024/07/26 19:24:33 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return(ERROR);
	return ((long long int)(time.tv_sec * 1000LL + (time.tv_usec + 500) / 1000));
}

int	ms_sleep(long long int mseconds)
{
	long long int	timer;
	long long int	start;
	long long int	current;

	timer = 0;
	current = 0;
	start = get_time_ms();
	if (start == ERROR)
		return (ERROR);
	while (timer < mseconds)
	{
		current = get_time_ms();
		if (current == ERROR)
			return (ERROR);
		timer = current - start;
		if (usleep(200) == -1)
			return (ERROR);
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
	d->philo[i]->lfork = &d->forks[i];
	d->philo[i]->rfork = &d->forks[(i + 1) % d->n_philos];
	d->philo[i]->death = 0;
	d->philo[i]->t_die = d->t_die;
	d->philo[i]->t_eat = d->t_eat;
	d->philo[i]->t_sleep = d->t_sleep;
	d->philo[i]->meals = d->meals;
	return (SUCCESS);
}

/*
	Forks (mutexes) start from 0
	Philos start from 0 + correspond to array index but their id is +1
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
	if (pthread_create(&d->butler, NULL, (void *)&butler, d) != SUCCESS)
			return (cleanerr(d, ETHREAD, 0));
	i = -1;
	while (++i < d->n_philos)
	{
		if (init_philo(d, i) != SUCCESS)
			return (cleanerr(d, EMALLOC, i));
		if (pthread_create(&(d->philo[i]->thread), NULL, (void *)&routine, d->philo[i])
			!= SUCCESS)
			return (cleanerr(d, ETHREAD, i));
	}
	return (SUCCESS);
}

int	initor(char **argv, t_data *d)
{
	d->n_philos = my_atoi(argv[1]);
	d->t_die = my_atoi(argv[2]);
	d->t_eat = my_atoi(argv[3]);
	d->t_sleep = my_atoi(argv[4]);
	d->meals = 0;
	if (argv[5])
		d->meals = my_atoi(argv[5]);
	if (init_mu_th(d) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
