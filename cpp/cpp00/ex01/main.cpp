// #include "PhoneBook.class.hpp"
#include "Contact.class.hpp"
#include <iostream>
#include <csignal>
#include <array>
#include <cstring>
#include <limits>

#ifndef YELLOW_CLR
# define YELLOW_CLR "\033[33m"
# define RESET_CLR "\033[0m"
#endif

void sig_exit(int sig)
{
	std::exit(sig);
}

void	do_cmd(std::array<char, 1024>& input)
{
	if (std::strcmp(input.data(), "ADD") == 0)
		std::cout << "adding..\n";
	else if (std::strcmp(input.data(), "SEARCH") == 0)
		std::cout << "searching..\n";
	else
		return ;
}

int	main (void)
{
	std::array<char, 1024>	input;
	PhoneBook				phonebook;
	(void)phonebook;

	input.fill(0);
	std::signal(SIGINT, sig_exit);
	std::signal(SIGQUIT, sig_exit);

	std::cout << "PhoneBook v0.1 TM\n";
	while (std::strcmp(input.data(), "EXIT") != 0)
	{
		input.fill(0);
		std::cout << YELLOW_CLR << "ADD, SEARCH, or EXIT:\n" << RESET_CLR;
		std::cin.getline(input.data(), input.size());
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Input limit is 1024 bytes!\n";
		}
		do_cmd(input);
	}
	return (0);
}