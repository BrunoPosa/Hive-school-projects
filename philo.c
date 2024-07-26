/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/07/26 18:39:43 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *p)
{
	while (1)
	{
		(void)p;
		printf("\n%lld id=%d\n", get_time_ms(), p->id);
		ms_sleep(1000);
	}
}

void	butler(t_data *d)
{
	(void)d;
	printf("\nbutler started\n");
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
