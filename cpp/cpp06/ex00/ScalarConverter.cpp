/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:23:23 by bposa             #+#    #+#             */
/*   Updated: 2025/04/05 15:24:20 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

using std::string;
using std::cout;
using std::endl;

// static bool convertToInt(const std::string& input, int& output) {
// 	if (input.empty()) return false;  // Empty string

// 	std::stringstream ss(input);
// 	ss >> output;

// 	// Check for failure (non-numeric input)
// 	if (ss.fail()) return false;

// 	// Check if there's leftover garbage in the stream
// 	char leftover;
// 	if (ss >> leftover) return false;

// 	return true;
// }

static	bool	isValid(const string& lit) {
	if (lit.find_first_not_of("infa-+.0123456789") != string::npos) {
		return false;
	}

	return true;
}

/*
	-detect type of literal passed (char, int, float, double)
	-convert from string to the actual type
	-convert explicitly to the other 3 types
	-display the results
	-if conversion makes no sense or overflows, print impossible
	
*/
void	ScalarConverter::convert(const string& literal) {
	
	if (literal.length() > 1) {
		if (isValid(literal) == false) {
			cout << YELLOWISH << "invalid argument!" << RESETISH << endl;
		}
	}
	//here goes case of empty string and of one char
	// toChar(literal);

	std::stringstream	ssInt(literal);
	int	ni;
	ssInt >> ni;
	cout << "int: " << ni << endl;

	std::stringstream	ssFloat(literal);
	float	nf;
	ssInt >> nf;
	cout << "float: " << nf << endl;
}