/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:10:26 by bposa             #+#    #+#             */
/*   Updated: 2025/02/16 19:10:11 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "ClapTrap.hpp"

int main()
{

	ScavTrap	gigi("Gigi");
	ScavTrap	gogo("Gogo");
	ClapTrap	bibi("Bibi");
	ClapTrap	bobo("Bobo");

	cout << endl;
	bibi.print();
	bobo.print();
	gigi.print();
	gogo.print();
	cout << endl;

	bobo.attack("Gigi");
	gigi.takeDamage(0);
	bibi.attack("Gigi");
	gigi.takeDamage(0);
	gogo.attack("Gigi");
	gigi.takeDamage(20);
	gigi.beRepaired(5);
	gigi.attack("Wrong person!");
	gogo.takeDamage(20);
	gigi.attack("Wrong person again!!");
	gogo.takeDamage(20);
	gigi.attack("Bibi");
	bibi.takeDamage(20);
	gogo.guardGate();

	cout << endl;
	bibi.print();
	bobo.print();
	gigi.print();
	gogo.print();
	cout << endl;

	gogo.attack("Gigi");
	gogo.attack("Gigi");
	gogo.attack("Gigi");
	gogo.attack("Gigi");
	gigi.takeDamage(80);
	gogo.guardGate();

	cout << endl;
	bibi.print();
	bobo.print();
	gigi.print();
	gogo.print();
}
