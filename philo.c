/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/08/04 13:36:27 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	-Why does sometimes philo N die at 1ms?
*/
void	routine(t_philo *p)
{
	edit_var(&p->ready, SUCCESS, &p->golock);
	while (!isdead(p))
	{
		wait_until(&p->ready, GO, &p->golock);
		printer(p->id, "is thinking", p);
		if (get_time_ms() - *p->start_t <= 1 && p->id % 2 == 0)
			wait_ms(1, p);
		pthread_mutex_lock(p->lfork);
		printer(p->id, "has taken a fork", p);
		if (!p->rfork)
		{
			pthread_mutex_unlock(p->lfork);
			break ;
		}
		pthread_mutex_lock(p->rfork);
		printer(p->id, "has taken a fork", p);
		printer(p->id, "is eating", p);
		p->last_meal_t = get_time_ms();
		wait_ms(p->eat_t, p);
		pthread_mutex_unlock(p->lfork);
		pthread_mutex_unlock(p->rfork);
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
		usleep(200);
	d->starttime = get_time_ms();
	spread(d, GO);
	while (1)
	{
		i = -1;
		while (++i < d->n_philos)
		{
			if (get_time_ms() - d->starttime == 0)
				d->philo[i]->last_meal_t = d->starttime;
			if (get_time_ms() - d->philo[i]->last_meal_t >= d->die_t) //improve this area
				spread(d, DEATH);
			if (isdead(d->philo[i]) || (checker(d, MEAL) == d->n_meals && d->n_meals != -1))
				break ;
		}
		if (checker(d, MEAL) == d->n_meals && d->n_meals != -1)
			spread(d, DEATH);
		if (d->death)
			break ;
	}
	if (d->death && (checker(d, MEAL) != d->n_meals || d->n_meals == -1))
		printer(d->philo[i]->id, "died", d->philo[i]);
}

void	spread(t_data *d, int signal)
{
	int	i;

	i = -1;
	if (signal == DEATH)
	{
		while (++i < d->n_philos)
			edit_var(&d->philo[i]->dead, DEATH, &d->philo[i]->dlock);
		d->death = DEATH;
	}
	else if (signal == GO)
	{
		while (++i < d->n_philos)
			edit_var(&d->philo[i]->ready, GO, &d->philo[i]->golock);
	}
}

//add mutex for death check
void	printer(int arg, char *str, t_philo *p)
{
	if (!isdead(p) || (isdead(p) && my_strncmp(str, "died", my_strlen(str)) == 0))
	{
		pthread_mutex_lock(p->prlock);
		printf("%lld %d %s\n", get_time_ms() - *p->start_t, arg, str);
		pthread_mutex_unlock(p->prlock);
		if (my_strncmp(str, "is eating", my_strlen(str)) == 0)
			p->meals_had++;
	}
	else if (my_strncmp(str, "is eating", my_strlen(str)) == 0)
	{
		pthread_mutex_unlock(p->lfork);
		pthread_mutex_unlock(p->rfork);
	}
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
	while (!d->death)
		usleep(100);
	return (cleanerr(d, SUCCESS, d->n_philos));
}
