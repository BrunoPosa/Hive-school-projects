/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/08/13 01:01:40 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	-ask Arthur about lack of forkswap with just the sleep_t / 3 delay. Seek edge cases.
	-delete bloat
	-norm pass
	-mock eval
*/
void	philolife(t_philo *p)
{
	setter(&p->ready, SUCCESS, &p->readylock);
	while (getter(&p->go, &p->golock) != GO)
		usleep(200);
	while (1)//!getter(&p->dead, &p->dlock))
	{
		// if (ifonlyonefork(p))
		// 	break ;
		if (routine(p) != SUCCESS || (p->meals != -1 && p->meals_had >= p->meals))
		{
			setter(&p->dead, p->id, &p->dlock);
			break ;
		}
	}
	setter(&p->end, 1, &p->readylock);
}

int	routine(t_philo *p)
{
	if (action(THINK, p->id, "is thinking", p))
		return (DEATH);
	if (p->id % 2 == 0) //!getter(&p->run, &p->readylock) && 
		wait_ms(p->sleep_t / 3, p);
	// else if (p->id % 2 == 0 && getter(&p->run, &p->readylock) == 1)
	// 	swapforks(p);
	pthread_mutex_lock(p->forkone);
	if (action(FORK, p->id, "has taken a fork", p))
		return (DEATH);
	if (!p->forktwo && lastmealset(p))
		return (ifonlyonefork(p));
	pthread_mutex_lock(p->forktwo);
	if (action(FORKEAT, p->id, "has taken a fork", p))
		return (DEATH);
	if (wait_ms(p->eat_t, p) != SUCCESS)
	{
		dropforks(p);
		return (DEATH);
	}
	dropforks(p);
	if (action(SLEEP, p->id, "is sleeping", p) || wait_ms(p->sleep_t, p))
		return (DEATH);
	p->run++;
	return (SUCCESS);
}

void	increment(int *var, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*var = *var + 1;
	if (*var == 2147483647)
		*var = 3;
	pthread_mutex_unlock(lock);
}

int	ifonlyonefork(t_philo *p)
{
	if (!p->forktwo)
	{
		// action(THINK, p->id, "is thinking", p);
		// pthread_mutex_lock(p->forkone);
		// printer(p->id, "has taken a fork", p);
		pthread_mutex_unlock(p->forkone);
		// wait_ms(p->die_t, p);
		setter(&p->dead, DEATH, &p->dlock);
		// setter(&p->end, 1, &p->readylock);
		return (DEATH);
	}
	return (ERROR);
}

void	dropforks(t_philo *p)
{
	pthread_mutex_unlock(p->forkone);
	pthread_mutex_unlock(p->forktwo);
}

void	swapforks(t_philo *p)
{
	pthread_mutex_t	*temp;

	temp = p->forkone;
	p->forkone = p->forktwo;
	p->forktwo = temp;
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
		if (p->meals)
		{
			printer(arg, "is eating", p);
			increment(&p->meals_had, &p->lmeallock);
			lastmealset(p);
		}
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
	long long int	t;

	i = -1;
	t = 0;
	while (checker(d, GO) != GO)
		usleep(200);
	d->starttime = get_time_ms();
	spread(d, GO);
	while (!getter(&d->death, &d->dielock))
	{
		i = -1;
		t = get_time_ms();
		while (++i < d->n_philos)
		{
			if ((lastmealget(d->philo[i]) != 0 && t - lastmealget(d->philo[i]) >= d->die_t)
				|| checker(d, MEAL) == SUCCESS)
			{
				spread(d, DEATH);
				break ;
			}
		}
		if (i != d->n_philos)
			break ;
	}//printf("\nn_meals:%d, meals_had by philo:%d\n\n", d->n_meals, d->philo[i]->meals_had);
	if (checker(d, MEAL) != SUCCESS)
		printf("%lld %d died\n", t - d->starttime, i + 1);
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
	while (endchecker(d) != SUCCESS)
		usleep(200);
	return (cleanerr(d, SUCCESS, d->n_philos));
}
