/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:50:51 by bposa             #+#    #+#             */
/*   Updated: 2025/02/24 17:48:29 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Brain
{
protected:
	string	_ideas[100];

public:
	Brain();
	Brain(const Brain& obj);
	Brain&	operator=(const Brain& obj);
	virtual ~Brain();
};

#endif
