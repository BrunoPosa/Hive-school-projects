/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:32:42 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 12:16:42 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(const std::string& name) : _name(name), _weaponType(nullptr) {}

void	HumanB::setWeapon(Weapon& weapon)
{
	_weaponType = &weapon;
}

void	HumanB::attack() const
{
	if (_weaponType != nullptr)
		std::cout << _name << " attacks with their " << _weaponType->getType() << std::endl;
	else
		std::cout << _name << " has no weapon!" << std::endl;
}