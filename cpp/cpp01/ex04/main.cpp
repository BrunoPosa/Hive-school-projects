/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:36:39 by bposa             #+#    #+#             */
/*   Updated: 2025/01/28 02:04:05 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replacer.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <csignal>
#include <exception>

# define SED_NEW_FILE_EXTENSION ".replace"
# define SED_FILENAME_MAX 255

/* Colors */
# define SED_RED "\e[31m"
# define SED_YELLOW "\033[33m"
# define SED_GREEN "\e[1;32m"
# define SED_RESETCLR "\033[0m"

enum e_errorCode
{
	SUCCESS,
	EXCEPTION,
	ARGUMENT_ERROR,
	EMPTY_FILENAME,
	FILENAME_TOO_LONG,
	FILE_OPEN_ERROR
};

bool	check(bool condition, const std::string& message)
{
	if (condition)
	{
		std::cout << SED_RED << "[ERROR]: " << SED_RESETCLR << message << std::endl;
		return (true);
	}
	return (false);
}

int	usageMsg(int errCode)
{
	std::cout << SED_YELLOW
			<< "usage: ./program <filename> <str to be replaced> <replacement str>"
			<< SED_RESETCLR << std::endl;
	return (errCode);
}

/*
	argv[1] - filename
	argv[2] - oldString
	argv[3] - newString
*/
int main(int argc, char **argv)
{
	int	status = 0;

	if (check(argc != 4, "there must be 3 arguments!"))
		return usageMsg(ARGUMENT_ERROR);
	
	try
	{
		Replacer	replacer(argv[1], argv[2], argv[3]);
		status = replacer.replace();
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return EXCEPTION;
	}
	if (status != SUCCESS)
		return usageMsg(status);
	return status;
}
