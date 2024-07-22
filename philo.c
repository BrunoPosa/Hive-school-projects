/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/07/22 16:19:44 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*live(t_data *d)
{
	(void)d;
	return (SUCCESS);
}

/*
	TODO:
	-fix validator() to work using macros
	-consider using memset() instead of my_bzero()
*/
int main(int argc, char **argv)
{
	t_data	*d;

	if (validator(argc, argv) == ERROR)
		return (msg(EVAL));
	d = malloc(sizeof(t_data));
	if (!d)
		return (msg(EMALLOC));
	memset(d, 0, sizeof(t_data));
	if (initor(argv, d) == ERROR)
		return (msg(EINIT));

printf("\n Yay! Program initialized successfully\n");

	cleanerr(d, SUCCESS, d->n_philos);
	return (SUCCESS);
}