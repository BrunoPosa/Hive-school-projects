/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:43:10 by bposa             #+#    #+#             */
/*   Updated: 2024/07/22 16:19:57 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#ifndef ERROR
# define ERROR -1
#endif

#ifndef SUCCESS
# define SUCCESS 0
#endif

#ifndef EARGC
# define EARGC 1
#endif

#ifndef EARG
# define EARG 2
#endif

#ifndef EINIT
# define EINIT 3
#endif

#ifndef ETHREAD
# define ETHREAD 4
#endif

#ifndef EMUTEX
# define EMUTEX 6
#endif

#ifndef EVAL
# define EVAL 7
#endif

#ifndef EMALLOC
# define EMALLOC 8
#endif

#ifndef MAX_PHILOS
# define MAX_PHILOS 10000
#endif

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef	struct	s_philo
{
	int				id;
	pthread_t		thread;
}	t_philo;

typedef struct	s_data
{
	t_philo			philo[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meals;
	int				death;
}	t_data;

t_data	*live(t_data *d);
int		validator(int argc, char **args);
int		initor(char **argv, t_data *d);
int		init_mu_th(t_data *d);
int		cleanerr(t_data *d, int status, int initialized);
int		msg(int status);
int		my_atoi(char *n);

#endif