/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replacer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:27:51 by bposa             #+#    #+#             */
/*   Updated: 2025/01/28 02:10:26 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLACER_HPP
# define REPLACER_HPP

#include <fstream>
#include <string>

class Replacer
{
	std::ifstream		_inFile;
	std::ofstream		_outFile;
	const std::string&	_oldStr;
	const std::string&	_newStr;

public:
	Replacer(const std::string& filename, const std::string& s1, const std::string& s2);
};

#endif