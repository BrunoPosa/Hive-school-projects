/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:22:15 by bposa             #+#    #+#             */
/*   Updated: 2025/03/02 22:42:44 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Animal
{
protected:
	string  _type;

public:
	Animal();
	Animal(const Animal& obj);
	Animal&	operator=(const Animal& obj);
	virtual ~Animal();

	virtual void	makeSound() const;
	string			getType() const;
};

#endif
