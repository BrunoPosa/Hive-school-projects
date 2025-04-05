/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:23:16 by bposa             #+#    #+#             */
/*   Updated: 2025/04/05 14:43:43 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

using std::string;
using std::cout;
using std::endl;

/*
	TODO:
	-class ScalarConverter OCF
	-"For each exercise, type conversion must be handled using a specific type of casting. Your choice will be reviewed during the defense."
	-is_scalar class
*/
int main (int ac, char** av) {
	if (ac != 2) {
		cout << "Give 1 argument!" << endl;
		return 1;
	}

	try {

		ScalarConverter::convert(av[1]);

	} catch (std::exception& e) {
		cout << REDISH << e.what() << RESETISH << endl;
	}

	return 0;
}