/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:53:42 by bposa             #+#    #+#             */
/*   Updated: 2025/04/06 15:57:48 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
// #include <cstdlib> //atoi, atof
#include <string>
#include <cctype> // isprint
// #include <sstream>
#include <limits> 

#define REDISH "\033[1;31m"
#define YELLOWISH "\033[33m"
#define GREENISH "\033[1;32m"
#define RESETISH "\033[0m"

#include <iomanip>
#include <cmath>
#include <cctype>
#include <regex>
#include <stdexcept>

class ScalarConverter {
	ScalarConverter()										= delete;
	ScalarConverter(const ScalarConverter& obj)				= delete;
	ScalarConverter &operator=(const ScalarConverter& obj)	= delete;
	~ScalarConverter()										= delete;
	
	public:
		static void convert(const std::string& literal);
};
