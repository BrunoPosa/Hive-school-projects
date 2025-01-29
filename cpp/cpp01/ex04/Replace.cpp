/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replace.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:46:24 by bposa             #+#    #+#             */
/*   Updated: 2025/01/29 04:00:47 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Replace.hpp"
#include <limits>

Replace::Replace(const string& filename, const string& str1, const string& str2)
	: _filename(filename), _oldStr(str1), _newStr(str2) {}

int	Replace::_printReturn(int status, const string& message)
{
	cout << SED_YELLOW << "[ERROR]: " << SED_RESETCLR << message << endl;
	return status;
}

int	Replace::_validate()
{
	if (_filename.empty())
		return _printReturn(EMPTY_FILENAME, "file name cannot be empty!");
	if (_filename.length() >= SED_FILENAME_MAX - sizeof(SED_NEW_FILE_EXTENSION))
		return _printReturn(FILENAME_TOO_LONG, "file name too long!");

	if (_oldStr.empty())
		return _printReturn(EMPTY_STRING, "string to be replaced cannot be empty!");

	if (_oldStr == _newStr)
		return _printReturn(STRINGS_IDENTICAL, "given strings are identical!");

	return SUCCESS;
}

string	Replace::_replaceInLine(const string& line)
{
	string	result;
	size_t	pos = 0;
	size_t	start = 0;

	if (line.length() < _oldStr.length())
		return result;
	while ((pos = line.find(_oldStr, start)) != string::npos)
	{
		result += line.substr(start, pos - start);
		result += _newStr;
		start = pos + _oldStr.length();
	}
	result += line.substr(start);
	return result;
}

int	Replace::run()
{
	int	status = _validate();
	if (status != SUCCESS)
		return status;

	std::ifstream	infile(_filename, std::ios::in);
	if (!infile)
		return _printReturn(INFILE_OPEN_ERROR, "file could not be opened!");

	std::ofstream	outfile(_filename + SED_NEW_FILE_EXTENSION, std::ios::out);
	if (!outfile)
		return _printReturn(OUTFILE_OPEN_ERROR, "new file could not be created!");

	string	line;
	while (std::getline(infile, line))
	{
		outfile << _replaceInLine(line) << endl;
		if (outfile.fail() == true)
			return _printReturn(WRITING_ERROR, "error writing to file!");
	}

	if (infile.eof() == false && infile.fail() == true)
		return _printReturn(READING_ERROR, "error reading the file!");

	return SUCCESS;
}
