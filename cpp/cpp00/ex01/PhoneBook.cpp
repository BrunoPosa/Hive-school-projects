/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:00:01 by bposa             #+#    #+#             */
/*   Updated: 2025/01/18 01:52:41 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.class.hpp"
#include <iomanip>
#include <limits>

PhoneBook::PhoneBook() : _index(0), _size(0) {};

bool	PhoneBook::addContact(void)
{
	std::string	first, last, nick, phone, secret;

	if (!_addField(first, "First Name") || 
		!_addField(last, "Last Name") || 
		!_addField(nick, "Nickname") || 
		!_addField(phone, "Phone Number") || 
		!_addField(secret, "Darkest Secret"))
		return false;

	_contacts[_toIndex()] = Contact(first, last, nick, phone, secret);
	if (getSize() != PB_SIZE)
		_size++;
	return (true);
}

unsigned int	PhoneBook::getSize(void)
{
	return (_size);
}

bool	PhoneBook::search(void)
{
	std::string		input;
	unsigned int	selection = 0;
	unsigned int	attempt = 0;

	if (_size == 0)
		return (false);
	for (unsigned int i = 0; i < _size; i++)
	{
		std::cout << std::setw(CONTACT_COLUMN_WIDTH) << i + 1 << "|";
		_contacts[i].showContactRow();
	}
	std::cout << std::endl << "Enter index of contact to display (out of " << _size << "):" << std::endl;
	while (true)
	{
		if (attempt >= PB_ATTEMPT_MAX || _inputFromStdin(input) == false)
			return (false);
		if (_isValidNumber(input, selection) == true && selection <= _size)
			break ;
		else
		{
			std::cout << "Selection does not exist! " << "(attempt " << attempt + 1
			<< " of " << PB_ATTEMPT_MAX << ")" << std::endl;
			attempt++;
		}
	}
	_contacts[selection - 1].showContactPage();

	return (true);
}

bool	PhoneBook::_addField(std::string& field, const std::string& label)
{
	unsigned int	attempt = 0;

	while (attempt < PB_ATTEMPT_MAX)
	{
		std::cout << "Entry " << 1 + (_index % PB_SIZE) << " - Type " << label << ":" << std::endl;
		if (_inputFromStdin(field) == false)
			return (false);
		else if (label == "Phone Number" && _isAllDigits(field) == false)
		{
			std::cout << "Use only digits! " << "(attempt " << attempt + 1
					<< " of " << PB_ATTEMPT_MAX << ")" << std::endl;
			field = "";
			attempt++;
		}
		else
			break ;
	}
	if (attempt >= PB_ATTEMPT_MAX || field.length() == 0)
		return (false);
	return (true);
}

bool	PhoneBook::_inputFromStdin(std::string& inputStr)
{
	unsigned int	attempt = 0;

	while (attempt < PB_ATTEMPT_MAX)
	{
		std::getline(std::cin, inputStr);
		if (std::cin.eof() == true)
		{
			std::cerr << "EOF." << std::endl;
			return (false);
		}
		else if (std::cin.fail() == true)
		{
			std::cerr << "Input stream error." << std::endl;
			return (false);
		}
		else if (inputStr.length() > PB_INPUTSTR_MAX)
		{
			std::cout << "Input too long! Max input is " << PB_INPUTSTR_MAX << " chars." << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			inputStr = "";
			attempt++;
            continue;
		}
		else if (inputStr.empty() == true)
		{
			std::cout << "Input cannot be empty!" << std::endl;
			attempt++;
			continue ;
		}
		return (true);
	}
	std::cout << "Too many attempts! Exiting.." << std::endl;
	return (false);
}

bool	PhoneBook::_isAllDigits(const std::string& inputStr)
{
	for (size_t i = 0; i < inputStr.length(); i++)
	{
		if (!std::isdigit(static_cast<unsigned char>(inputStr[i]))) {
			return (false);
		}
	}
	return (true);
}

bool	PhoneBook::_isValidNumber(const std::string& inputStr, unsigned int& result)
{
	std::stringstream	ss(inputStr);
	ssize_t				num;

	if (_isAllDigits(inputStr) == false)
		return (false);
	ss >> num;
	if (ss.fail() || num <= 0)
		return (false);
	result = num;
	return (true);
}

unsigned int	PhoneBook::_toIndex(void)
{
	if (_index == PB_SIZE)
		_index = 0;
	return (_index++);
}
