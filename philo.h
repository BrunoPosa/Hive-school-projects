#ifndef PHILO_H
# define PHILO_H

#ifndef ERROR
# define ERROR -1
#endif

#ifndef SUCCESS
# define SUCCESS 0
#endif

#ifndef ARGC
# define ARGC 1
#endif

#ifndef ARG
# define ARG 2
#endif

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

#include <stdio.h>
#include <unistd.h>

int	validator(int argc, char **args);
int	errs(int status);

#endif