/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:00:01 by bposa             #+#    #+#             */
/*   Updated: 2025/01/15 02:30:45 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.class.hpp"
#include <cstring>

PhoneBook::PhoneBook() : _index(0) {};

bool	PhoneBook::add_field(std::string& field, const std::string& label)
{

	while (field.length() > MAIN_INPUT_BUFFER_SIZE || field.length() == 0)
	{
		if (std::cin.fail() == true && (field.length() <= MAIN_INPUT_BUFFER_SIZE && field.length() != 0))
		{
			std::cin.clear();
			return (false);
		}
		std::cin.clear();
		std::cout << "Entry " << 1 + (_index % PHONEBOOK_SIZE)
				<< " - Type " << label << ":" << std::endl;
		std::getline(std::cin, field);
	}
	return (true);
}

bool	PhoneBook::add_contact(void)
{
	std::string	first, last, nick, phone, secret;

	if (!add_field(first, "First Name") || 
		!add_field(last, "Last Name") || 
		!add_field(nick, "Nickname") || 
		!add_field(phone, "Phone Number") || 
		!add_field(secret, "Darkest Secret"))
		return false;

	_contacts[toIndex()] = Contact(first, last, nick, phone, secret);
	return (true);
}

/*
Todo: check for valid numbers both in index, and in phone number z

	You can use std::stoi (or std::stol, std::stoll for larger numbers) in combination with std::cin.fail() 
	to check if the string can be converted to an integer. However, this approach would require handling 
	exceptionsor checking input validity.
*/
bool	PhoneBook::search()
{
	unsigned int displayIndex = 0;

	for (unsigned int i = 0; i < _index; i++) {
		_contacts[i].showContactRow();
	}

	// std::cout << std::endl << "Enter index of contact to display (0 to " << _index - 1 << "):" << std::endl;
	// while (true) {
    //     std::cin >> displayIndex;

    //     // Check if input failed (invalid input)
    //     if (std::cin.fail()) {
    //         std::cin.clear();  // Reset fail state
    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
    //         std::cout << "Please enter a valid number.\n";
    //     } else {
    //         // Valid input, break out of loop
    //         break;
    //     }
	// }

	// _contacts[_indexCheck(displayIndex)].showContactPage();

	return (true);
}

unsigned int	PhoneBook::_indexCheck(unsigned int i)
{
	return (i);
}

unsigned int	PhoneBook::toIndex(void)
{
	if (_index > PHONEBOOK_SIZE - 1)
		_index = 0;
	return (_index++);
}