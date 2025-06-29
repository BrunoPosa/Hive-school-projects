/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:51:34 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 12:09:39 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie*		Zombie::zombieHorde(int N, std::string name)
{
	if (N <= 0 || name.empty() == true)
		return (nullptr);

	Zombie*	horde = new (std::nothrow) Zombie[N];
	if (horde == nullptr)
	{
		std::cout << "Allocation failed!" << std::endl;
		return (nullptr);
	}

	for (int i = 0; i < N; i++) {
		horde[i]._name = name + std::to_string(i);
	}

	return (horde);
}