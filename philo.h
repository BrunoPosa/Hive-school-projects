/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:43:10 by bposa             #+#    #+#             */
/*   Updated: 2024/07/31 20:24:03 by bposa            ###   ########.fr       */
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

#ifndef DEATH
# define DEATH 616
#endif

#ifndef MAX_PHILOS
# define MAX_PHILOS 4000
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
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*prlock;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				meals_had;
	int				*dead;
	long long int	last_meal_t;
	long long int	*start_t;
	int				error;
	int				*go;
}	t_philo;

typedef struct	s_data
{
	pthread_t		butler;
	t_philo			*philo[MAX_PHILOS];
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_mutex_t	printlock;
	int				n_philos;
	int				die_t;
	int				eat_t;
	int				sleep_t;
	int				n_meals;
	long long int	starttime;
	int				death;
	int				go;
}	t_data;

void			routine(t_philo *p);
void			butler(t_data *d);
int				validator(int argc, char **args);
int				initor(char **argv, t_data *d);
int				init_mu_th(t_data *d);
long long int	get_time_ms(void);
int				wait_ms(long long int mseconds, t_philo *p);
int				cleanerr(t_data *d, int status, int initialized);
int				ermsg(int status);
void			printer(int arg, char *str, t_philo *p);
int				my_atoi(char *n);
size_t			my_strlen(const char *s);
int				my_strncmp(const char *s1, const char *s2, size_t n);

#endif