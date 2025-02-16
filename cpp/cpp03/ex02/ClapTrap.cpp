/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:05:01 by bposa             #+#    #+#             */
/*   Updated: 2025/02/15 18:11:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

/*	Orthodox Canonical Form members	*/

ClapTrap::ClapTrap() : _hitPts(10), _energyPts(10), _atkDamage(0) {
	cout <<	"ClapTrap Default constructor called." << endl;
};

ClapTrap::ClapTrap(const ClapTrap& obj)
	: _name(obj._name), _hitPts(obj._hitPts), _energyPts(obj._energyPts), _atkDamage(obj._atkDamage) {
		cout << "ClapTrap Copy constructor called." << endl;
}

ClapTrap&	ClapTrap::operator=(const ClapTrap& obj) {
	if (this == &obj) {
		return *this;
	}
	_name = obj._name;
	_hitPts = obj._hitPts;
	_energyPts = obj._energyPts;
	_atkDamage = obj._atkDamage;
	cout << "ClapTrap Copy assignment operator called." << endl;

	return *this;
}

ClapTrap::~ClapTrap() {	cout << "ClapTrap Destructor called." << endl;	}



/*	Overloads	*/

ClapTrap::ClapTrap(const string& name) : _name(name), _hitPts(10), _energyPts(10), _atkDamage(0) {
	cout <<	"ClapTrap Constructor called." << endl;
};



/*	Member functions	*/

void	ClapTrap::attack(const string& target) {
	if (_hitPts > 0 && _energyPts > 0) {
		--_energyPts;
		cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _atkDamage << " points of damage!" << endl;
	}
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (_hitPts > 0 && _energyPts > 0) {
		_hitPts -= amount;
		cout << "ClapTrap " << _name << " gets " << amount << " damage!" << endl;
	}
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (_hitPts > 0 && _energyPts > 0) {
		--_energyPts;
		_hitPts += amount;
		cout << "ClapTrap " << _name << " is repaired with " << amount << " hit points!" << endl;
	}
}


void	ClapTrap::print() {
	cout << "\033[33m" << _name << " has " << _hitPts << " hitPts, " << _energyPts << " energyPts, and can cause " << _atkDamage << " damage." << "\033[0m" << endl;
}