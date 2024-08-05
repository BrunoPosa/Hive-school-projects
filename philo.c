/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/08/05 23:45:26 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	-consider having status for each philo
	(maybe a subroutine function too, which will be locked by one mutex
	instead of having every action locked)
*/
void	routine(t_philo *p)
{
	setter(&p->ready, SUCCESS, &p->readylock);
	wait_until(&p->go, GO, &p->golock);
	while (!isdead(p))
	{
		printer(p->id, "is thinking", p);
		if (p->last_meal_t == 0 && p->id % 2 == 0)
			wait_ms(1, p);
		pthread_mutex_lock(p->forkone);
		printer(p->id, "has taken a fork", p);
		if (!p->forktwo && lastmealset(p))
		{
			pthread_mutex_unlock(p->forkone);
			break ;
		}
		pthread_mutex_lock(p->forktwo);
		printer(p->id, "has taken a fork", p);
		printer(p->id, "is eating", p);
		lastmealset(p);
		wait_ms(p->eat_t, p);
		pthread_mutex_unlock(p->forkone);
		pthread_mutex_unlock(p->forktwo);
		printer(p->id, "is sleeping", p);
		if (isdead(p) || wait_ms(p->sleep_t, p) == DEATH)
			break ;
	}
}

void	butler(t_data *d)
{
	int	i;

	i = -1;
	while (checker(d, GO) != GO)
		usleep(400);
	d->starttime = get_time_ms();
	spread(d, GO);
	while (1)
	{
		i = -1;
		while (++i < d->n_philos)
		{
			if (d->philo[i]->last_meal_t != 0 
				&& get_time_ms() - lastmealget(d->philo[i]) >= d->die_t)
				spread(d, DEATH);
			if (isdead(d->philo[i]) || checker(d, MEAL) == SUCCESS)
				break ;
		}
		if (checker(d, MEAL) == SUCCESS)
			spread(d, DEATH);
		if (d->death)
			break ;
	}
	if (getter(&d->death, &d->dielock) && checker(d, MEAL) != SUCCESS)
		printer(d->philo[i]->id, "died", d->philo[i]);
}

void	spread(t_data *d, int signal)
{
	int	i;

	i = -1;
	if (signal == DEATH)
	{
		while (++i < d->n_philos)
			setter(&d->philo[i]->dead, DEATH, &d->philo[i]->dlock);
		setter(&d->death, DEATH, &d->printlock);
	}
	else if (signal == GO)
	{
		while (++i < d->n_philos)
			setter(&d->philo[i]->go, GO, &d->philo[i]->golock);
	}
}

void	printer(int arg, char *str, t_philo *p)
{
	int printed;

	printed = 0;
	if (!isdead(p) || (isdead(p) && my_strncmp(str, "died", my_strlen(str)) == 0))
	{
		pthread_mutex_lock(p->prlock);
		printf("%lld %d %s\n", get_time_ms() - *p->start_t, arg, str);
		pthread_mutex_unlock(p->prlock);
		printed = 1;
		if (my_strncmp(str, "is eating", my_strlen(str)) == 0)
			p->meals_had++;
	}
	else if (printed && my_strncmp(str, "is eating", my_strlen(str)) == 0)
	{
		pthread_mutex_unlock(p->forkone);
		pthread_mutex_unlock(p->forktwo);
	}
	// else if (!printed && isdead(p))
	// 	pthread_mutex_unlock(p->forkone);
}

/*
	THINK --> EAT --> SLEEP --> THINK --> EAT
	-fix validator() to work using macros/enums
	-reorganize initialization
	-Limit philos in validation to 4000? + Malloc instead of static alloc, bc valgrind
	-"\e[31m Error \e[0m\n" colors
	-use Enums for error codes
	-Consider having a synced simulation starting time in case of many philos
	-ensure when someone dies, NOTHING gets ever printed after that
*/
int main(int argc, char **argv)
{
	t_data	*d;

	if (validator(argc, argv) == ERROR)
		return (ermsg(EVAL));
	d = malloc(sizeof(t_data));
	if (!d)
		return (ermsg(EMALLOC));
	if (initor(argv, d) == ERROR)
		return (ermsg(EINIT));
	wait_until(&d->death, DEATH, &d->printlock);
	return (cleanerr(d, SUCCESS, d->n_philos));
}
