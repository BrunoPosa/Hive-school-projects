/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:36:39 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 12:42:41 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"
#include <iostream>
#include <exception>

int	printUsageReturn(int errCode)
{
	if (errCode != SUCCESS)
	{
		cout << SED_YELLOW
			<< "usage: ./Sed_is_for_losers <filename> <str to be replaced> <replacement str>"
			<< SED_RESETCLR << endl;
	}
	return errCode;
}
/*
	Test:
	-s1 is a substring of s2
	-binary file
	-run when output file already exists
*/
int main(int argc, char **argv)
{
	int	status = 0;

	if (argc != 4)
	{
		cout << SED_YELLOW << "there must be 3 arguments!" << SED_RESETCLR << endl;
		return printUsageReturn(ARGUMENT_ERROR);
	}
	try
	{
		Replace	replacer(argv[1], argv[2], argv[3]);
		status = replacer.run();
	}
	catch (const std::exception& e)
	{
		cout << "Fatal Error: " << e.what() << endl;
		return EXCEPTION;
	}
	return printUsageReturn(status);
}
