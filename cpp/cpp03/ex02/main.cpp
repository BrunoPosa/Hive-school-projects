/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:10:26 by bposa             #+#    #+#             */
/*   Updated: 2025/02/17 15:40:47 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include "ClapTrap.hpp"

int main()
{
	FragTrap	frog("Froggie");
	ClapTrap	clog("Cloggie");

	cout << endl;
	frog.print();
	clog.print();
	cout << endl;

	frog.attack("Mom");
	clog.takeDamage(30);
	frog.highFivesGuys();
	frog.beRepaired(42);
	clog.beRepaired(42);
	clog.attack("Space, shaking fist in air angrily");
	cout << endl;

	ClapTrap	avenger("Starkie Tony");
	avenger.beRepaired(10000);
	FragTrap	thanos("Tiki Tiki");
	frog = thanos;
	avenger.attack("Frogsmith lineage");
	frog.takeDamage(10000);
	thanos.takeDamage(1000);
	FragTrap(frog);

	cout << endl;
	frog.print();
	clog.print();
	avenger.print();
	return 0;
}