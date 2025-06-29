/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:25:22 by bposa             #+#    #+#             */
/*   Updated: 2025/01/21 15:02:03 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.class.hpp"
#include "PhoneBook.class.hpp"

#include <csignal>

void sig_exit(int sig)
{
	std::exit(sig);
}

bool	do_cmd(PhoneBook& phonebook, std::string& input)
{
	if (input == "ADD" && phonebook.addContact() == false)
		return (false);
	else if (input == "SEARCH")
	{
		if (phonebook.getSize() == 0)
		{
			std::cout << "Silly Billy! Add a contact first! Closing.." << std::endl;
			return (false);
		}
		if (phonebook.search() == false)
			return (false);
	}
	return (true);
}

/*
	test cases:
	-try SEARCH when there is no contacts
	-redirect an empty file as input
	-Try very long line and empty line
	-see if there is leaks on Ctrl+C or \
	-see if adding limit+1 contacts loops over
	-special chars mess the table bc they are > 1 byte

	To fix:
	-delete 'class' from header file names
	-ensure each file has a 42 header
	-if not needed to exit, do not exit..
	-std::cin.ignore is unecessary in inputFromStdin()
*/
int	main (void)
{
	std::string	input;
	PhoneBook	phonebook;

	std::signal(SIGINT, sig_exit);
	std::signal(SIGQUIT, sig_exit);
 
	/* Welcome message */
	std::cout << PB_GREEN << "============ Awesome PhoneBook V.0.1 ============" << PB_RESET_COLOR << std::endl
			<< PB_GREEN << "Up to " << PB_SIZE << " contacts with "
			<< PB_INPUTSTR_MAX << "-byte fields" << PB_RESET_COLOR << std::endl
			<< "Each contact's fields are:" << std::endl
			<< "first name, last name, nickname, phone number, darkest secret" << std::endl;

	while (input != "EXIT")
	{
		std::cout << PB_YELLOW << "ADD, SEARCH, or EXIT:" << PB_RESET_COLOR << std::endl;
		if (!std::getline(std::cin, input))
		{
			if (std::cin.eof() == true)
			{
				std::cout << "EOF!" << std::endl;
				return (0);
			}
			else if (std::cin.fail())
				return (5);
		}
		if (do_cmd(phonebook, input) == false)
			return (1);
	}
	std::cout << "[Contacts deleted, Bye! :P]" << std::endl;
	return (0);
}