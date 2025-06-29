/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:50:22 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 12:09:29 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main (void)
{
	ssize_t	number = 0;
	Zombie	*zzZs;
	Zombie z = Zombie("og");

	z.announce();

	zzZs = z.zombieHorde(0, "ZAmbie");
	if (zzZs != nullptr)
		delete[] zzZs;

	/* successfully allocating */
	number = 5;
	if (!(zzZs = z.zombieHorde(number, "ZOmbie")))
		return (1);
	for (int i = 0; i < number; i++)
		zzZs[i].announce();
	delete[] zzZs;

	/* returns nullptr */
	zzZs = z.zombieHorde(-7, "ZImbie");
	if (zzZs != nullptr)
		delete[] zzZs;

	/* returns nullptr as (int)__SIZE_MAX__ overflows) */
	number = __SIZE_MAX__;
	if (!(zzZs = z.zombieHorde(number, "ZEmbie")))
		return (1);
	delete[] zzZs;

	return (0);
}