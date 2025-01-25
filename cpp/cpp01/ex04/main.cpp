/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:36:39 by bposa             #+#    #+#             */
/*   Updated: 2025/01/25 01:40:31 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include ""
#include <string>
#include <iostream>
#include <fstream>
#include <csignal>

# define SED_FILE_EXTENSION ""
# define SED_FNAME_MAX 256 //syslimit=255, but we subtract sizeof(FILE_EXTENSION) which counts \0

/* Colors */
# define SED_RED "\e[31m"
# define SED_YELLOW "\033[33m"
# define SED_GREEN "\e[1;32m"
# define SED_RESETCLR "\033[0m"

enum errorCode
{
	SUCCESS,
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

void sig_exit(int sig)
{
	std::cout << "Signal " << sig << " received. Exiting..." << std::endl;
	std::exit(sig);
}

int	openReplaceSaveTo(std::string &fname, std::string &s1, std::string &s2, std::string newFname)
{

}

/*

*/
int main(int argc, char **argv)
{
	std::signal(SIGINT, sig_exit);
	std::signal(SIGQUIT, sig_exit);

	if (check(argc != 4, "there must be 3 arguments!"))
		return usageMsg(ARGUMENT_ERROR);

	std::string filename = argv[1];

	if (check(filename.empty(), "file name cannot be empty!"))
		return EMPTY_FILENAME;

	if (check(filename.length() >= SED_FNAME_MAX - sizeof(SED_FILE_EXTENSION), "file name too long!"))
		return FILENAME_TOO_LONG;

	std::string outputFilename = filename + SED_FILE_EXTENSION;
	std::string str1 = argv[2];

	if (check(str1.empty(), "string to be replaced cannot be empty!"))
		return EMPTY_FILENAME;
	std::string str2 = argv[3];

	if ()
	return (openReplaceSaveTo(filename, str1, str2, outputFilename));
}