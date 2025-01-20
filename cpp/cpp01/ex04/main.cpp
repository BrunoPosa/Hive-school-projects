/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:36:39 by bposa             #+#    #+#             */
/*   Updated: 2025/01/20 19:48:34 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ""
#include <string>
#include <ios>
#include <iostream>

# define SED_YELLOW "\033[33m"
# define SED_GREEN "\e[1;32m"
# define SED_RESETCLR "\033[0m"

/*
	Test:
	-nonexistant filenames, file w/o permission
	-empty file, special file (/dev/null ..), file modifyed during reading
	-file size limits
	-binary file
	-
*/
int main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cout << SED_YELLOW << "usage: ./program <filename> <str being replaced> <new str>"
			<< SED_RESETCLR << std::endl;
		return (0);
	}
	return (0);
}