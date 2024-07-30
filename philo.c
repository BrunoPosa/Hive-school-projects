/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/07/30 21:26:04 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	-Time slip more proportional to larger n_philos, 1-2 ms every second
	-change the flag pointers to variables (make butler cycle through each updating them)
*/
void	routine(t_philo *p)
{
	while (!*p->dead)
	{
		while (!*p->go)
			usleep(100);
		printer(p->id, "is thinking", p);
		if (get_time_ms() - *p->start_t <= 1 && p->id % 2 == 0)
			wait_ms(1, p);
		pthread_mutex_lock(p->lfork);
		printer(p->id, "has taken a fork", p);
		pthread_mutex_lock(p->rfork);
		printer(p->id, "has taken a fork", p);
		printer(p->id, "is eating", p);
		p->last_meal_t = get_time_ms();
		wait_ms(p->eat_t, p);
		pthread_mutex_unlock(p->lfork);
		pthread_mutex_unlock(p->rfork);
		printer(p->id, "is sleeping", p);
		if (*p->dead || wait_ms(p->eat_t, p) == DEATH)
			break ;
	}
	printf("%d exit\n", p->id);
}

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
			{
				d->death = d->philo[i]->id;
				break ;
			}
		}
		if (d->death)
			break ;
		wait_ms(1, d->philo[i]);
	}
	printf("%lld %d died\n", get_time_ms() - d->starttime, d->philo[i]->id);
	printf("\e[33mbutler exit\e[0m\n");
}
/*
	THINK --> EAT --> SLEEP --> THINK --> EAT
	-shuffle routine so odd number of philos can manage the forks and live (play w think_t?)
	-fix validator() to work using macros/enums
	-reorganize initialization
	-Limit philos in validation to 4000? + Malloc instead of static alloc, bc valgrind
	-"\e[31m Error \e[0m\n" colors
	-use Enums for error codes
	-Consider having a synced simulation starting time in case of many philos
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
	// usleep(500000);
	return (cleanerr(d, SUCCESS, d->n_philos));
}
