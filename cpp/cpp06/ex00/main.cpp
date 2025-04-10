/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:23:16 by bposa             #+#    #+#             */
/*   Updated: 2025/04/10 18:12:57 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
using std::string;
using std::cout;
using std::endl;

int main (int ac, char** av) {
	if (ac != 2) {
		cout << "Give 1 argument!" << endl;
		return 1;
	}

	try {

		ScalarConverter::convert(av[1]);

	} catch (std::exception& e) {
		cout << "exception in main: " << REDISH << e.what() << RESETISH << endl;
	}

	return 0;
}