/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:40:18 by bposa             #+#    #+#             */
/*   Updated: 2025/02/02 13:04:32 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main (void) {
	Fixed	a(5);
	cout << a << endl;
	Fixed	b(5);

	// Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

	cout << (b < a) << endl;
	cout << (b > a) << endl;
	cout << (b == a) << endl;
	cout << (b != a) << endl << endl;

std::cout << (a + b).toFloat() << std::endl;  // Should print 10.0
	// cout << ++a << endl;
	// cout << a << endl;
	// cout << a++ << endl;
	// cout << a << endl;
	// cout << b << endl;
	// cout << Fixed::max( a, b ) << endl;

	return 0;
}
