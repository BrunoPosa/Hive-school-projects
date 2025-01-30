/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 01:26:01 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 12:06:43 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie	newScope(Zombie og2, Zombie* zombiePointer, Zombie** pointer)
{
	Zombie	scopedZombie = Zombie("scopedZombie");
	*pointer = scopedZombie.newZombie("zombieFromBelow");

	std::cout << "\033[33m" << std::endl; // set yellow output

	scopedZombie.announce();
	og2.announce();
	zombiePointer->announce();

	return (scopedZombie);
}

int	main (void)
{
	Zombie	og = Zombie("og");
	Zombie*	ptr = nullptr;
	Zombie*	john = og.newZombie("John");
	Zombie*	paul = og.newZombie("Paul");
	
	if (john == nullptr || paul == nullptr)
		return (1);
	og.randomChump("og's rando");
	john->announce();
	paul->announce();
	john->randomChump("john's rando");
	paul->randomChump("paul's rando");

	newScope(og, paul, &ptr).announce();
	if (ptr == nullptr)
		return (1);
	ptr->announce();
	std::cout << "\033[0m" << std::endl; //remove yellow output

	delete john;
	delete paul;
	delete ptr;
	return (0);
}