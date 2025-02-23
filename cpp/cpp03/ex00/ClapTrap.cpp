/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:05:01 by bposa             #+#    #+#             */
/*   Updated: 2025/02/22 21:52:03 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

/*	Orthodox Canonical Form members	*/

ClapTrap::ClapTrap() : _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	cout <<	"Default constructor called." << endl;
};

ClapTrap::ClapTrap(const ClapTrap& obj)
	: _name(obj._name), _hitPoints(obj._hitPoints), _energyPoints(obj._energyPoints), _attackDamage(obj._attackDamage) {
		cout << "Copy constructor called." << endl;
}

ClapTrap&	ClapTrap::operator=(const ClapTrap& obj) {
	cout << "Copy assignment operator called." << endl;
	if (this != &obj) {
		_name = obj._name;
		_hitPoints = obj._hitPoints;
		_energyPoints = obj._energyPoints;
		_attackDamage = obj._attackDamage;
	}
	return *this;
}

ClapTrap::~ClapTrap() {	cout << "Destructor called." << endl;	}



/*	Overloads	*/

ClapTrap::ClapTrap(const string& name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	cout <<	"Constructor called." << endl;
};



/*	Member functions	*/

void	ClapTrap::attack(const string& target) {
	if (_hitPoints > 0 && _energyPoints > 0) {
		--_energyPoints;
		cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << endl;
	}
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (_hitPoints > 0 && _energyPoints > 0) {
		_hitPoints = (amount > _hitPoints) ? 0 : _hitPoints - amount;
		cout << "ClapTrap " << _name << " gets " << amount << " damage!" << endl;
	}
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (_hitPoints > 0 && _energyPoints > 0) {
		--_energyPoints;
		_hitPoints = (_hitPoints > __UINT32_MAX__ - amount) ? __UINT32_MAX__ : _hitPoints + amount;
		cout << "ClapTrap " << _name << " is repaired with " << amount << " hit points!" << endl;
	}
}


void	ClapTrap::print() {
	cout << "\033[33m" << _name << " has " << _hitPoints << " hitPts, " << _energyPoints << " energyPts, and can cause " << _attackDamage << " damage." << "\033[0m" << endl;
}
