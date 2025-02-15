/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:10:26 by bposa             #+#    #+#             */
/*   Updated: 2025/02/15 18:42:16 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "ClapTrap.hpp"

int main (void)
{
	cout << "main" << endl;

	// ClapTrap a;
	// a.attack("bro");

	ScavTrap b;
	// b.attack("mentality");
	// b.print();
	ScavTrap(b).print();
	ScavTrap c = b;
	// cout << b._atkDamage << endl;
	cout << endl;
	ScavTrap("Hobo");
	return 0;
}