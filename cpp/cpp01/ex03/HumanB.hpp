/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:33:02 by bposa             #+#    #+#             */
/*   Updated: 2025/01/20 01:39:07 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

#include "Weapon.hpp"

class HumanB
{
	std::string	_name;
	Weapon*		_weaponType;

public:
	HumanB(const std::string& name);

	void setWeapon(Weapon& weaponType);
	void attack() const;
};

#endif