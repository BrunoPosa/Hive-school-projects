#include "philo.h"

/*	TODO
	-validate arguments to be in subject scope (is 1ms too little for arg?)
	-initialize/alloc needed variables and start timers and threads, checking for failures
	-
*/
/* What if a thread fails, do I need to do smth w/ it?*/
int errs(int status)
{
	if (status == ARGC)
	{
		if (write(2, "\nUsage:\n        ./philo Philos T_die T_eat"
			" T_sleep [optional: Meals]\n", 69) == ERROR)
			return (5);
		return (ERROR);
	}
	if (status == ARG)
	{
		if (write(2, "\nEach argument must be 0-9999\n"
			"\nUsage:\n        ./philo Philos T_die T_eat"
			" T_sleep [optional: Meals]\n", 99) == ERROR)
			return (5);
		return (ERROR);
	}
	if (status == ERROR)
		return (ERROR);
	return (0);
}

int main(int argc, char **argv)
{
	if (validator(argc, argv) == ERROR)
		return (ERROR);
	
	return (0);
}