/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:04:38 by bposa             #+#    #+#             */
/*   Updated: 2025/02/15 16:06:02 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class ClapTrap
{
protected:
	string	_name;
	int		_hitPts;
	int		_energyPts;
	int		_atkDamage;

public:
	ClapTrap();
	ClapTrap(const ClapTrap& obj);
	ClapTrap&	operator=(const ClapTrap& obj);
	~ClapTrap();
	ClapTrap(const string& name);

	void	attack(const string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);

	void	print();
};

#endif
