/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:33:25 by bposa             #+#    #+#             */
/*   Updated: 2025/01/20 01:40:03 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_CLASS_HPP
# define HUMANA_CLASS_HPP

#include "Weapon.class.hpp"

class HumanA
{
	std::string	_name;
	Weapon&		_weaponType;

public:
	HumanA(const std::string& name, Weapon& weapon);

	void attack() const;
};

#endif