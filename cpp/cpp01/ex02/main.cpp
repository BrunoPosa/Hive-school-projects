/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:24:09 by bposa             #+#    #+#             */
/*   Updated: 2025/01/19 14:22:48 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>

/*
	References a la GPT: Alias for a variable:
    -A reference acts as an alternative name for a variable.
    	Any operation on the reference directly affects the original variable.
	-Must be initialized at declaration:
	    You must assign a reference to an existing variable when you declare it.
	-Cannot be null:
	    Unlike pointers, references must always refer to a valid object.
	-No reseating:
    	A reference cannot be changed to refer to another variable after initialization.
*/
int main(void)
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

	return (0);
}