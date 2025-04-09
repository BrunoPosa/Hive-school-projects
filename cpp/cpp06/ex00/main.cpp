/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:23:16 by bposa             #+#    #+#             */
/*   Updated: 2025/04/10 02:35:17 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
using std::string;
using std::cout;
using std::endl;

/*
TODO:
-"For each exercise, type conversion must be handled using a specific type of casting. Your choice will be reviewed during the defense."
-is_scalar class
-correct for stoi overdlow to print impossible
-check stof stod overflowing
-play with "'c'"
-consider if float/double mantisa rounding errors are a concern
*/
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