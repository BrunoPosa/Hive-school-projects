/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:33:44 by bposa             #+#    #+#             */
/*   Updated: 2024/07/22 16:39:41 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (pthread_create(&d->philo[i].thread, NULL, (void *)&live, d) != SUCCESS)
			return (cleanerr(d, ETHREAD, i));
		i++;
	}
	return (SUCCESS);
}

/*
	TODO:
	-Initialilze condition variables?
*/
int	initor(char **argv, t_data *d)
{
	d->n_philos = my_atoi(argv[1]);
	if (init_mu_th(d) != SUCCESS)
		return (ERROR);
	d->t_die = my_atoi(argv[2]);
	d->t_eat = my_atoi(argv[3]);
	d->t_sleep = my_atoi(argv[4]);
	d->meals = 0;
	if (argv[5])
		d->meals = my_atoi(argv[5]);
	return (SUCCESS);
}
