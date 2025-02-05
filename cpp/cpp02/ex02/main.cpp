/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:40:18 by bposa             #+#    #+#             */
/*   Updated: 2025/02/05 17:33:54 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main (void) {
{
	cout << "\n===Example main===" << endl << endl;

	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;
}
{
	cout << "\n===My main===" << endl << endl;

	Fixed	a(0);
	cout << a << endl;
	Fixed	b(2);

	cout << (b < a) << endl;
	cout << (b > a) << endl;
	cout << (b == a) << endl;
	cout << (b != a) << endl << endl;

	// Fixed const c( Fixed( 5.05f ) * Fixed( 2 ) );
	// cout << c << endl;

	// cout << (a + b) << endl;
	// cout << "minus" << (a - b) << endl;
	// cout << (a * b) << endl;
	// cout << a << " / " << b << "= " << (a / b) << endl;
cout << "increments" << endl;
	cout << (++a) << endl;
	cout << a << endl;
	cout << (a++) << endl;
	cout << a << endl << endl;
cout << "decrements" << endl;
	cout << (--a) << endl;
	cout << a << endl;
	cout << (a--) << endl;
	cout << a << endl;
	// cout << b << endl;
	// cout << Fixed::max( a, b ) << endl;

}
	return 0;
}
