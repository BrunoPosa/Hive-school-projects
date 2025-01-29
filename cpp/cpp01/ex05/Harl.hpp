/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:00:48 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 00:32:18 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

#include <string>
#include <iostream>

# define HARL_TOTAL 4 //up to USHRT_MAX

# define HARL_YELLOW "\033[33m"
# define HARL_RESETCLR "\033[0m"

using std::cout;
using std::endl;
using std::string;

class Harl
{
	void	(Harl::*_comments[HARL_TOTAL])();
	string	_levels[HARL_TOTAL];

	void	_debug();
	void	_info();
	void	_warning();
	void	_error();

public:
	Harl();
	void	complain(string level);
};

#endif