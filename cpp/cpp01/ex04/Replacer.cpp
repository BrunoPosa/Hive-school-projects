/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replacer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:46:24 by bposa             #+#    #+#             */
/*   Updated: 2025/01/28 02:11:27 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replacer.hpp"

Replacer::Replacer(const std::string& filename, const std::string& s1, const std::string& s2) {}

int	Replacer::replace()
{
	std::string	filename(argv[1]);
	if (check(filename.empty(), "file name cannot be empty!"))
		return (EMPTY_FILENAME);
	if (check(filename.length() >= SED_FILENAME_MAX - sizeof(SED_NEW_FILE_EXTENSION), "file name too long!"))
		return (FILENAME_TOO_LONG);

	std::string	str1(argv[2]);
	if (check(str1.empty(), "string to be replaced cannot be empty!"))
		return (EMPTY_FILENAME);

	std::string	outputFilename(filename + SED_NEW_FILE_EXTENSION);
	std::string	str2(argv[3]);

	return replace(filename, str1, str2, outputFilename);
}
