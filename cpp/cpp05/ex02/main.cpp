/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:24:46 by bposa             #+#    #+#             */
/*   Updated: 2025/03/21 18:08:19 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	-test the virtual destruction (e.g. use heap and cheack for leaks)
*/
#include <type_traits>
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main (void) {
	static_assert(std::is_abstract<AForm>::value, "AForm must be an abstract class!");
	// ShrubberyCreationForm c;
	// cout << c << endl;
	ShrubberyCreationForm a("k");
	ShrubberyCreationForm b(a);
	cout << a << endl;
	cout << b << endl;
}