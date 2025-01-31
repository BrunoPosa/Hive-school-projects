/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:00:18 by bposa             #+#    #+#             */
/*   Updated: 2025/01/31 17:27:26 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int	main(void) {

	Fixed	a;
	Fixed	b(a);
	Fixed	c;

	c = b;
	cout << a.getRawBits() << endl;
	cout << b.getRawBits() << endl;
	cout << c.getRawBits() << endl;

	// a.setRawBits(7);
	// b.setRawBits(8);
	// c.setRawBits(9);
	// cout << a.getRawBits() << endl;
	// cout << b.getRawBits() << endl;
	// cout << c.getRawBits() << endl;
}