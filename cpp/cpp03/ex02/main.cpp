/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 21:10:26 by bposa             #+#    #+#             */
/*   Updated: 2025/02/17 14:31:14 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include "ClapTrap.hpp"

int main()
{
	FragTrap	frog("Froggie");

	frog.attack("Mom");
	frog.print();
	frog.highFivesGuys();
	frog.beRepaired(1);
	frog.print();
	return 0;
}