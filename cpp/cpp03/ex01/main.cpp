/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:10:26 by bposa             #+#    #+#             */
/*   Updated: 2025/02/23 00:07:41 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "ClapTrap.hpp"
#include <exception>

int main()
{
	try {
		ClapTrap	*fufu = new ScavTrap();
		ScavTrap	sisi("sisi");
		ScavTrap	soso("soso");
		ClapTrap	cici("cici");
		ClapTrap	coco("coco");
		ScavTrap	copy(sisi);
		copy = soso;
		fufu->attack("Self");
		delete fufu;

		cout << endl;
		cici.print();
		coco.print();
		sisi.print();
		soso.print();
		copy.print();
		cout << endl;

		soso.attack("sisi");
		sisi.takeDamage(20);
		sisi.beRepaired(__UINT32_MAX__);
		soso.takeDamage(__UINT32_MAX__);
		soso.guardGate();
		sisi.guardGate();

		cout << endl;
		sisi.print();
		soso.print();
		cout << endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
