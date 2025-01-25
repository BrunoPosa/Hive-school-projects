/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:27:51 by bposa             #+#    #+#             */
/*   Updated: 2025/01/25 02:27:15 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <iostream>
#include <fstream>
#include <string>

/* FileHandler object needs to be checked! */
class InFile
{
	std::fstream	_file;

public:
	InFile(const std::string& filename);

	std::fstream&	getFileStream();
};

InFile::FileHandler(const std::string& filename) : _file(filename, std::ios::in | std::ios::out) {}
