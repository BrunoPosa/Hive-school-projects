/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:05:16 by bposa             #+#    #+#             */
/*   Updated: 2025/02/10 20:49:36 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main (void)
{
{
	string name = "Doozy";
	ClapTrap a(name);
	a.print();
	a.attack("Helno");
	a.print();
	a.beRepaired(5);
	a.print();
	a.takeDamage(2);
	a.print();
	cout << endl << endl;
}
{
	ClapTrap	a("CT A");
	ClapTrap	b("CT B");

	a.print();
	b.print();
	b.takeDamage(3);
	a.takeDamage(6);
	a.attack("CT B");
	b.attack("noob1");
	a.print();
	b.print();
	b.beRepaired(4);
	b.attack("CT B");
	b.attack("CT B");
	a.beRepaired(1);
	a.print();
	b.print();
	b.takeDamage(12);
	a.takeDamage(9);
	a.beRepaired(5);
	b.attack("CT3");
	a.print();
	b.print();
	b.takeDamage(12);
	b.print();
}
	return 0;

}