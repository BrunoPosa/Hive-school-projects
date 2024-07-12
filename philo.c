/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:28:33 by bposa             #+#    #+#             */
/*   Updated: 2024/07/12 13:56:46 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* What if a thread fails, do I need to do smth w/ it?*/
int errs(int status)
{
	if (status == EARGC)
	{
		if (write(2, "\nUsage:\n        ./philo Philos T_die T_eat"
			" T_sleep [optional: Meals]\n", 69) == ERROR)
			return (5);
		return (ERROR);
	}
	if (status == EARG)
	{
		if (write(2, "\nEach argument must be 0-9999\n"
			"--> Usage:\n        ./philo Philos T_die T_eat"
			" T_sleep [optional: Meals]\n", 102) == ERROR)
			return (5);
		return (ERROR);
	}
	if (status == ERROR)
		return (ERROR);
	return (0);
}

/*
	init TODO:

	1. Initialize the mutexes and condition variables needed for synchronization.
	2. Create threads for each philosopher.
	3. Set up timers for each philosopher to track their eating time.
	4. Implement the logic for the philosopher's behavior (eating, thinking, sleeping).
	5. Handle any errors that may occur during initialization.
	6. Clean up any resources (mutexes, condition variables, threads) before exiting the program.
*/
// static int	init()
// {	
// 	// TODO: Initialize mutexes and condition variables

// 	// TODO: Create threads for each philosopher

// 	// TODO: Set up timers for each philosopher

// 	// TODO: Implement philosopher's behavior

// 	// TODO: Handle initialization errors

// 	// TODO: Clean up resources
// 	return (SUCCESS);
// }

int main(int argc, char **argv)
{
	if (validator(argc, argv) == ERROR)
		return (ERROR);
	
	return (0);
}