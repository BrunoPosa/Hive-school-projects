/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:50:51 by bposa             #+#    #+#             */
/*   Updated: 2025/03/02 20:39:20 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

#define BRAINSIZE 100

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Brain
{
	string			_ideas[BRAINSIZE];
	unsigned int	_index;

public:
	Brain();
	Brain(const Brain& obj);
	Brain&	operator=(const Brain& obj);
	~Brain();

	void	addIdea(const string& newIdea);
	void	printAll() const;
};

#endif
