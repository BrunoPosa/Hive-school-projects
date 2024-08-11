/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/08/12 00:07:59 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	-Philo dies after some time with 200 130 60 60
	-it still sometimes prints "taken a fork" after death, e.g. with 200 130 60 60
	-try testing w/ fast debug optimization flag
	-./philo 200 599 200 200 should not die at 600 i think, but it often does. 
		AND rarely has some prints after death. 199 599 200 200 SHOUOLD die though.
	-Fix Helgrind
	-198 6 200 200 when giving small die_t, the printing continues a while after death
	-test 200 800 200 200 (none should die) Arthur fixed with every
		odd taking one fork first and even the other - BUT only on first run through. 
		Also waiting for sleep_t/2 to look for forks.
*/
void	philolife(t_philo *p)
{
	setter(&p->ready, SUCCESS, &p->readylock);
	while (getter(&p->go, &p->golock) != GO)
		usleep(200);
	while (!getter(&p->dead, &p->dlock))
	{
		if (action(THINK, p->id, "is thinking", p))
			break ;
		if (routine(p) != SUCCESS)// || (p->meals_had != -1 && p->meals_had >= p->meals)
			break ;
	}
}

int	routine(t_philo *p)
{
	if (getter(&p->firstrun, &p->readylock) && p->id % 2 == 0)
		wait_ms(p->sleep_t / 2, p);
	pthread_mutex_lock(p->forkone);
	if (action(FORK, p->id, "has taken a fork", p))
		return (DEATH);
	if (!p->forktwo && lastmealset(p))
		return (ERROR);
	pthread_mutex_lock(p->forktwo);
	if (action(FORKEAT, p->id, "has taken a fork", p) || wait_ms(p->eat_t, p))
		return (DEATH);
	pthread_mutex_unlock(p->forkone);
	pthread_mutex_unlock(p->forktwo);
	if (action(SLEEP, p->id, "is sleeping", p) || wait_ms(p->sleep_t, p))
		return (DEATH);
	setter(&p->firstrun, 0, &p->readylock);
	return (SUCCESS);
}

int	action(t_action act, int arg, char *str, t_philo *p)
{
	pthread_mutex_lock(&p->dlock);
	if (p->dead)
	{
		if (act == FORK)
			pthread_mutex_unlock(p->forkone);
		else if (act == FORKEAT)
		{
			pthread_mutex_unlock(p->forkone);
			pthread_mutex_unlock(p->forktwo);
		}
		pthread_mutex_unlock(&p->dlock);
		return (DEATH);
	}
	printer(arg, str, p);
	if (act == FORKEAT)
	{
		printer(arg, "is eating", p);
		p->meals_had++;
		lastmealset(p);
	}
	pthread_mutex_unlock(&p->dlock);
	return (SUCCESS);
}

void	printer(int arg, char *str, t_philo *p)
{
	pthread_mutex_lock(p->prlock);
	printf("%lld %d %s\n", get_time_ms() - *p->start_t, arg, str);
	pthread_mutex_unlock(p->prlock);
}

void	butler(t_data *d)
{
	int	i;

	i = -1;
	while (checker(d, GO) != GO)
		usleep(200);
	d->starttime = get_time_ms();
	spread(d, GO);
	while (!getter(&d->death, &d->dielock))
	{
		i = -1;
		while (++i < d->n_philos)
		{
			if ((d->philo[i]->last_meal_t != 0 
				&& get_time_ms() - lastmealget(d->philo[i]) >= d->die_t)
				|| checker(d, MEAL) == SUCCESS)
			{
				spread(d, DEATH);
				break ;
			}
		}
		if (i != d->n_philos)
			break ;
	}
	if (checker(d, MEAL) != SUCCESS)
		printer(d->philo[i]->id, "died", d->philo[i]);
}

int	spread(t_data *d, int signal)
{
	int	i;

	i = -1;
	if (signal == DEATH)
	{
		while (++i < d->n_philos)
			setter(&d->philo[i]->dead, DEATH, &d->philo[i]->dlock);
		setter(&d->death, DEATH, &d->dielock);
	}
	else if (signal == GO)
	{
		while (++i < d->n_philos)
			setter(&d->philo[i]->go, GO, &d->philo[i]->golock);
	}
	return (SUCCESS);
}

/*
	-Implement mutex lock/unlock protections..
	-fix validator() to work using macros/enums
	-reorganize initialization
	-Limit philos in validation to 2000
	-ensure when someone dies, NOTHING gets ever printed after that
*/
int main(int argc, char **argv)
{
	t_data	*d;

	if (validator(argc, argv) == ERROR)
		return (ermsg(EVAL));
	d = malloc(sizeof(t_data));
	if (!d)
		return (ermsg(EMALMUT));
	if (initor(argv, d) == ERROR)
		return (ermsg(EINIT));
	d->initdone = 1;
	while (getter(&d->death, &d->dielock) != DEATH)
		usleep(400);
	return (cleanerr(d, SUCCESS, d->n_philos));
}
