/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:27:51 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 13:04:10 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACE_HPP
# define REPLACE_HPP

#include <fstream>
#include <string>
#include <iostream>

# define SED_NEW_FILE_EXTENSION ".replace"
# define SED_FILENAME_MAX 255

# define SED_RED "\e[31m"
# define SED_YELLOW "\033[33m"
# define SED_GREEN "\e[1;32m"
# define SED_RESETCLR "\033[0m"

using std::cout;
using std::string;
using std::endl;

enum e_errorCode
{
	SUCCESS,
	EXCEPTION,
	ARGUMENT_ERROR,
	EMPTY_FILENAME,
	EMPTY_STRING,
	FILENAME_TOO_LONG,
	INFILE_OPEN_ERROR,
	OUTFILE_OPEN_ERROR,
	STRINGS_IDENTICAL,
	READING_ERROR,
	WRITING_ERROR
};

/**
 * @class Replace
 * @brief Performs string replacement operations on file contents.
 *
 * Replaces all occurrences of s1 with s2 in the file <filename>.
 * The results are written to a new file "<filename>.replace".
 *
 * @note Use try-catch blocks to handle potential exceptions from string operations.
 *
 * Example usage:
 * @code
 * try {
 *     Replace replacer("example.txt", "oldString", "newString");
 *     int result = replacer.run();
 *     if (result != SUCCESS) {
 *         // Handle error
 *     }
 * } catch (const std::exception& e) {
 *     std::cerr << "Exception: " << e.what() << std::endl;
 * }
 * @endcode
 */
class Replace
{
	const string	_filename;
	const string	_oldStr;
	const string	_newStr;

	int				_printReturn(int status, const string& message);
	int				_validate();
	string			_replaceInLine(const string& line);

public:
	Replace(const string& filename, const string& s1, const string& s2);

	int run();
};

#endif