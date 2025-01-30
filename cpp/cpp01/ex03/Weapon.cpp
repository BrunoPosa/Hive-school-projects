/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:30:41 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 12:21:54 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type) : _type(type) {}

const std::string&	Weapon::getType() const
{
	return (_type);
}

void	Weapon::setType(std::string type)
{
	if (type.empty() == true)
		std::cout << "Weapon type cannot be empty!" << std::endl;
	else
		_type = type;
}