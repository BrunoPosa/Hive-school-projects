/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:33:11 by bposa             #+#    #+#             */
/*   Updated: 2025/01/20 01:40:50 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.class.hpp"

HumanA::HumanA(const std::string& name, Weapon& weapon) : _name(name), _weaponType(weapon) {}

void HumanA::attack() const
{
    std::cout << _name << " attacks with their " << _weaponType.getType() << std::endl;
}