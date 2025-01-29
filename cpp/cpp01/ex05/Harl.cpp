/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:01:22 by bposa             #+#    #+#             */
/*   Updated: 2025/01/30 00:52:08 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl() :
	_comments{
		&Harl::_debug,
		&Harl::_info,
		&Harl::_warning,
		&Harl::_error},
	_levels{
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"} {}

void	Harl::complain(string level)
{
	for (unsigned short i = 0; i < HARL_TOTAL; i++)
	{
		if (level == _levels[i])
		{
			(this->*_comments[i])();
			return ;
		}
	}
	cout << HARL_YELLOW << "Unknown level!" << HARL_RESETCLR << endl;
}
void	Harl::_debug() {	cout << HARL_YELLOW << "Debug!" << HARL_RESETCLR << endl;	}

void	Harl::_info()
{
	cout << HARL_YELLOW << "FYInfo: Voyager 1 is >24 billion "
	"kilometers away, in interstellar space." << HARL_RESETCLR << endl;
}

void	Harl::_warning() {	cout << HARL_YELLOW << "Staph that! I'm warning you." << HARL_RESETCLR << endl;	}

void	Harl::_error() {	cout << HARL_YELLOW << "~Errrrror~" << HARL_RESETCLR << endl;	}
