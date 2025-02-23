/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:05:16 by bposa             #+#    #+#             */
/*   Updated: 2025/02/22 22:53:10 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <exception>

int	main (void)
{
	ClapTrap one("One");
	ClapTrap two("Two");
	ClapTrap three;
	ClapTrap	copy(one);
	one.print();
	two.print();
	three.print();
	copy.print();
	three = one;
	three.print();
	cout << endl;

	one.attack("Two");
	two.takeDamage(2);
	two.beRepaired(1);
	two.print();
	one.print();
	cout << endl;

	one.beRepaired(__UINT32_MAX__);
	one.print();
	one.takeDamage(1000000000);
	one.print();
	one.takeDamage(__UINT32_MAX__);
	one.beRepaired(__UINT32_MAX__);

	cout << endl;
	one.print();
	two.print();
	cout << endl;

	return 0;
}
