/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:51:29 by bposa             #+#    #+#             */
/*   Updated: 2025/02/16 18:47:49 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

/*	Orthodox Canonical Form members - base class overloads	*/

ScavTrap::ScavTrap() {
	_hitPts = 100;
	_energyPts = 50;
	_atkDamage = 20;
	cout << "ScavTrap Default Constructor called." << endl;
}

ScavTrap::ScavTrap(const ScavTrap& obj) : ClapTrap(obj) {
	cout << "ScavTrap Copy Constructor called." << endl;
}

ScavTrap&	ScavTrap::operator=(const ScavTrap& obj) {
	if (this != &obj) {
		ClapTrap::operator=(obj);
		cout << "ScavTrap Copy assignment operator called." << endl;
	}
	return *this;
}

ScavTrap::~ScavTrap() {	cout << "ScavTrap Destructor called." << endl;	}



/*	Overloads	*/

ScavTrap::ScavTrap(const string& name) : ClapTrap(name) {
	_hitPts = 100;
	_energyPts = 50;
	_atkDamage = 20;
	cout <<	"ScavTrap Constructor called." << endl;
}

void	ScavTrap::attack(const string& target) {
	if (_hitPts > 0 && _energyPts > 0) {
		--_energyPts;
		cout << "ScavTrap " << _name << " attacks " << target << ", causing " << _atkDamage << " points of damage!" << endl;
	}
}



/*	New Member Functions	*/

void	ScavTrap::guardGate() {
	cout << "ScavTrap Gate Keeper mode ON" << endl;
}
