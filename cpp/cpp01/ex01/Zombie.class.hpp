/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:51:53 by bposa             #+#    #+#             */
/*   Updated: 2025/01/19 00:02:17 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_CLASS_HPP
# define ZOMBIE_CLASS_HPP

#include <iostream>

class	Zombie
{
	std::string	_name;

public:
	Zombie() = default;
	Zombie(std::string name);
	~Zombie();

	void		announce();
	Zombie*		zombieHorde(int N, std::string name);
};

#endif