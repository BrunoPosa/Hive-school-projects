/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:33:44 by bposa             #+#    #+#             */
/*   Updated: 2024/07/23 19:58:02 by bposa            ###   ########.fr       */
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

int	my_usleep(long long int mseconds)
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

/*
	Forks (mutexes) go 0-99
	Philos id's go 1-100
*/
int	init_mu_th(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->n_philos)
	{
		if (pthread_mutex_init(&d->forks[i], NULL) != SUCCESS)
			return (cleanerr(d, EMUTEX, i));
		i++;
	}
	i = 0;
	while (i < d->n_philos)
	{
		if (pthread_create(&d->philo[i].thread, NULL, (void *)&routine, d)
			!= SUCCESS)
			return (cleanerr(d, ETHREAD, i));
		d->philo[i].id = i + 1;
		i++;
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
