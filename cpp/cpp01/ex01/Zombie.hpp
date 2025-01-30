/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:51:53 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 12:31:43 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <string>

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