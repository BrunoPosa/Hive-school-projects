/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:24:09 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 12:14:58 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <exception>

int main(void)
{
	try
	{
		std::string str = "HI THIS IS BRAIN";
		std::string *stringPTR = &str;
		std::string &stringREF = str;

		std::cout << "Addresses" << std::endl;
		std::cout << std::setw(10) << "String:" << &str << std::endl;
		std::cout << std::setw(10) << "Pointer:" << stringPTR << std::endl;
		std::cout << std::setw(10) << "Reference:" << &stringREF << std::endl;

		std::cout << std::endl << "Values" << std::endl;
		std::cout << std::setw(10) << "String:" << str << std::endl;
		std::cout << std::setw(10) << "Pointer:" << *stringPTR << std::endl;
		std::cout << std::setw(10) << "Reference:" << stringREF << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}