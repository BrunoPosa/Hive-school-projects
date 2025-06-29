/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:14:48 by bposa             #+#    #+#             */
/*   Updated: 2025/02/23 00:55:27 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

/*	Orthodox Canonical Form members - base class overloads	*/

FragTrap::FragTrap() {
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	cout << "FragTrap Default Constructor called." << endl;
}

FragTrap::FragTrap(const FragTrap& obj) : ClapTrap(obj) {
	cout << "FragTrap Copy Constructor called." << endl;
}

FragTrap&	FragTrap::operator=(const FragTrap& obj) {
	if (this != &obj) {
		ClapTrap::operator=(obj);
		cout << "FragTrap Copy assignment operator called." << endl;
	}
	return *this;
}

FragTrap::~FragTrap() {	cout << "FragTrap Destructor called." << endl;	}



/*	Overloads	*/

FragTrap::FragTrap(const string& name) : ClapTrap(name) {
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	cout <<	"FragTrap Constructor called." << endl;
}



/*	New Member Functions	*/

void	FragTrap::highFivesGuys() {
	if (_hitPoints > 0 && _energyPoints > 0) {
		cout << "FragTrap's Positive high-fives request granted." << endl;
	}
}
