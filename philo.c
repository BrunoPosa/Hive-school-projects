/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/07/26 21:05:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	How do i free anything from here on error? Maybe handle error handling last?
*/
void	routine(t_philo *p)
{
	while (1)
	{
		if (p->id % 2 != 0)
		{
			if (pthread_mutex_lock(p->lfork) != SUCCESS)
				p->error = 1;
			printf("%lld %d has taken a fork\n", get_time_ms() - p->starttime, p->id);
			if (pthread_mutex_lock(p->rfork) != SUCCESS)
				p->error = 1;
			printf("\n%lld %d has taken a fork\n", get_time_ms() - p->starttime, p->id);
			printf("\n%lld %d is eating\n", get_time_ms() - p->starttime, p->id);
			ms_sleep(p->t_eat);
			if (pthread_mutex_unlock(p->lfork) != SUCCESS)
				p->error = 1;
			if (pthread_mutex_unlock(p->rfork) != SUCCESS)			
				p->error = 1;
				
		}
		else
		{
			if (pthread_mutex_lock(p->rfork) == SUCCESS)
				printf("\n%lld %d has taken a fork\n", get_time_ms() - p->starttime, p->id);
			if (pthread_mutex_lock(p->lfork) == SUCCESS)
				printf("%lld %d has taken a fork\n", get_time_ms() - p->starttime, p->id);
			printf("\n%lld %d is eating\n", get_time_ms() - p->starttime, p->id);
			ms_sleep(p->t_eat);
		}
	}
}

void	butler(t_data *d)
{
	(void)d;
	printf("butler started\n");
	ms_sleep(1000);
}
/*
	TODO:
	-fix validator() to work using macros
	-reorganize initialization
	-have a conductor()/monitor function to run the simulation
	-Limit philos in validation and header to 4000
	-"\e[31m Error \e[0m\n"
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

	cleanerr(d, SUCCESS, d->n_philos);
	return (SUCCESS);
}
