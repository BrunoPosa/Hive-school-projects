/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/08/03 19:02:43 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	-make death as mutex that i un/lock bc now the philos keep thinking after death
	-Why does sometimes philo N die at 1ms?
	-change the flag pointers to variables/mutexes (make butler cycle through each updating them)
*/
void	routine(t_philo *p)
{
	while (!*p->dead)
	{
		while (!*p->go)
			usleep(200);
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
		if (*p->dead || wait_ms(p->sleep_t, p) == DEATH)
			break ;
	}
}

//make sure nothing gets printed after death (might need a death mutex for that, or just by focusing on printing)
void	butler(t_data *d)
{
	int	i;

	i = -1;
	wait_ms(500, d->philo[0]);
	d->starttime = get_time_ms();
	d->go = 1;
	while (1)
	{
		i = -1;
		while (++i < d->n_philos)
		{
			if (get_time_ms() - d->starttime == 0)
				d->philo[i]->last_meal_t = d->starttime;
			if (get_time_ms() - d->philo[i]->last_meal_t >= d->die_t)
				d->death = d->philo[i]->id;
			if (d->death || (mealchecker(d) == d->n_meals && d->n_meals != -1))
				break ;
		}
		if (mealchecker(d) == d->n_meals && d->n_meals != -1)
			d->death = -1;
		if (d->death)
			break ;
		wait_ms(1, d->philo[0]);
	}
	if (d->death && (mealchecker(d) != d->n_meals || d->n_meals == -1))
		printer(d->philo[i]->id, "died", d->philo[i]);
}

//add mutex for death check
void	printer(int arg, char *str, t_philo *p)
{
	if (!*p->dead || (*p->dead && my_strncmp(str, "died", my_strlen(str)) == 0))
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
