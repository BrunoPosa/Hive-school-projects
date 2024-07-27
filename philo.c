/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/07/27 19:54:03 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	How do i free anything from here on error? Maybe handle error handling last?
	Will this th be joined on error before butler gets the memo?
*/
void	routine(t_philo *p)
{
	while (1)//get_time_ms() - p->last_meal_t < p->die_t
	{
		if (get_time_ms() - p->start_t == 0 && p->id % 2 == 0)
		{
			if (wait_ms(2, p) != SUCCESS)
				break ;
		}
		pthread_mutex_lock(p->lfork);
		// pthread_mutex_lock(p->prlock);
		printf("%lld %d has taken a fork\n", get_time_ms() - p->start_t, p->id);
		// pthread_mutex_unlock(p->prlock);
		pthread_mutex_lock(p->rfork);
		// pthread_mutex_lock(p->prlock);
		printf("%lld %d has taken a fork\n", get_time_ms() - p->start_t, p->id);
		// pthread_mutex_unlock(p->prlock);
		if (p->die_t < get_time_ms() - p->last_meal_t)
			break ;
		p->last_meal_t = get_time_ms();
		// pthread_mutex_lock(p->prlock);
		printf("%lld %d is eating\n", p->last_meal_t - p->start_t, p->id);
		// pthread_mutex_unlock(p->prlock);
		if (wait_ms(p->eat_t, p) != SUCCESS)
			break ;
		pthread_mutex_unlock(p->lfork);
		pthread_mutex_unlock(p->rfork);
		// pthread_mutex_lock(p->prlock);
		printf("%lld %d is thinking\n", get_time_ms() - p->start_t, p->id);
		// pthread_mutex_unlock(p->prlock);
		// if (wait_ms(get_time_ms() - , p) != SUCCESS)
		// 	break ;
		// pthread_mutex_lock(p->prlock);
		printf("%lld %d is sleeping\n", get_time_ms() - p->start_t, p->id);
		// pthread_mutex_unlock(p->prlock);
		if (wait_ms(p->sleep_t, p) != SUCCESS)
			break ;
	}
	p->error = 1;
}

/*
	-do i call cleanerr() here or leave it only in main?
	-Michael says philos checking themselves for death is slow (4 310 200 100), so maybe butler should check
*/
void	*butler(t_data *d)
{
	int	i;

	i = 0;
	while (d->philo[i]->dead != 1 || d->philo[i]->error != 1)
	{
		i = -1;
		while (++i < d->n_philos)
		{
			if (d->philo[i]->dead == 1 || d->philo[i]->error == 1)
				break ;
		}
	}
	if (d->philo[i]->dead == 1)
	{
		// pthread_mutex_lock(&d->printlock);
		printf("%lld %d died\n", get_time_ms() - d->philo[i]->start_t, d->philo[i]->id);
		// pthread_mutex_unlock(&d->printlock);
		d->error_death = 1;
		cleanerr(d, DEATH, d->n_philos);
	}
	if (d->philo[i]->error == 1)
	{
		d->error_death = 1;
		cleanerr(d, ERROR, d->n_philos);
	}
	return (SUCCESS);
}
/*
	TODO:
	-fix validator() to work using macros/enums
	-reorganize initialization
	-Limit philos in validation and header to 4000?
	-"\e[31m Error \e[0m\n" colors
	-use Enums for error codes
*/
int main(int argc, char **argv)
{
	t_data	*d;

	if (validator(argc, argv) == ERROR)
		return (ermsg(EVAL));
	d = malloc(sizeof(t_data));
	if (!d)
		return (ermsg(EMALLOC));
	memset(d, 0, sizeof(t_data));
	if (initor(argv, d) == ERROR)
		return (ermsg(EINIT));
	if (d->error_death == 1)
		return (ERROR);
printf("Herer!");
	return (SUCCESS);//cleanerr(d, SUCCESS, d->n_philos)
}
