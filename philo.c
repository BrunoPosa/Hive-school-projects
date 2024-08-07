/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/08/07 16:13:29 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	-consider having status for each philo
	(maybe a subroutine function too, which will be locked by one mutex
	instead of having every action locked)
	-consider  mutex golock_even + golock_odd with *golock
	-Philo dies after some time with 200 130 60 60
	-it still sometimes prints "taken a fork" after death, e.g. with 200 130 60 60
	-it does not work with odd number of philos and 130 60 60
	-dies at 400 every sometime with 3 599 200 200
*/
void	routine(t_philo *p)
{//usleep(5000);printf("routine : %d\n", p->id);
	setter(&p->ready, SUCCESS, &p->readylock);
	while (getter(&p->go, &p->golock) != GO)
		usleep(400);
	while (getter(&p->dead, &p->dlock) != DEATH)
	{
		printer(p->id, "is thinking", p);
		if (p->id % 2 == 0)
			wait_ms(5, p);
		pthread_mutex_lock(p->forkone);
		printer(p->id, "has taken a fork", p);
		if (p->last_meal_t == 0 && !p->forktwo && lastmealset(p))
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
		if (getter(&p->dead, &p->dlock) == DEATH || wait_ms(p->sleep_t, p))
			break ;
	}
}

void	butler(t_data *d)
{//usleep(3000);printf("butler:%d\n", d->death);
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

void	printer(int arg, char *str, t_philo *p)
{
	if (getter(&p->dead, &p->dlock) == DEATH && my_strncmp(str, "died", 4) != SUCCESS)
		return ;
	pthread_mutex_lock(p->prlock);
	printf("%lld %d %s\n", get_time_ms() - *p->start_t, arg, str);
	if (my_strncmp(str, "died", 4) != SUCCESS)
		pthread_mutex_unlock(p->prlock);
	if (my_strncmp(str, "is eating", 9) == 0)
		p->meals_had++;
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
	d->initflag = 1;
	// printf("Main\n");
	while (getter(&d->death, &d->dielock) != DEATH)
		usleep(400);
	pthread_join(d->butler, NULL);
	return (cleanerr(d, SUCCESS, d->n_philos));
}
