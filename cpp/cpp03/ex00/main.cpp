/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:05:16 by bposa             #+#    #+#             */
/*   Updated: 2025/02/17 15:43:55 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main (void)
{
	string name = "Doozy";
	ClapTrap a(name);
	a.print();
	a.attack("Helno");
	a.print();
	a.beRepaired(5);
	a.print();
	a.takeDamage(2);
	a.print();
	cout << endl << endl;
	return 0;

}