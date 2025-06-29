/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 10:40:18 by bposa             #+#    #+#             */
/*   Updated: 2025/02/05 19:53:50 by bposa            ###   ########.fr       */
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
	std::cout << Fixed::max(a, b) << std::endl;
}
{

	cout << "\n=== My main ===\n" << endl;

    Fixed a;
    cout << "a = " << a << endl;

    Fixed b(2);
    cout << "b = " << b << endl;

    // Comparison operators
    cout << "\nComparison operators:\n";
    cout << b << " < " << a << " = " << (b < a) << endl;
    cout << b << " > " << a << " = " << (b > a) << endl;
    cout << b << " == " << a << " = " << (b == a) << endl;
    cout << b << " != " << a << " = " << (b != a) << endl;

    // Multiplication example
    Fixed const c(Fixed(5.05f) * Fixed(2));
    cout << "\nFixed const c = " << c << endl;

    // Arithmetic operations
    cout << "\nArithmetic operators:\n";
    cout << a << " + " << b << " = " << (a + b) << endl;
    cout << a << " - " << b << " = " << (a - b) << endl;
    cout << a << " * " << b << " = " << (a * b) << endl;
    cout << a << " / " << b << " = " << (a / b) << endl;

    // Increment and decrement operators
    cout << "\nIncrement/Decrement operators:\n";
	cout << "a at start = " << a << endl;
    cout << "Pre-increment: " << (++a) << endl;
    cout << "After pre-increment: " << a << endl;
    cout << "Post-increment: " << (a++) << endl;
    cout << "After post-increment: " << a << endl;

    cout << "\nDecrement operators:\n";
    cout << "Pre-decrement: " << (--a) << endl;
    cout << "After pre-decrement: " << a << endl;
    cout << "Post-decrement: " << (a--) << endl;
    cout << "After post-decrement: " << a << endl;

    // Min comparison
    cout << "\nMin comparison:\n";
    cout << b << " is the minimum of " << a << " and " << b << ": "
         << ((Fixed::min(a, b) == a) ? "false" : "true") << endl;

}
	return 0;
}
