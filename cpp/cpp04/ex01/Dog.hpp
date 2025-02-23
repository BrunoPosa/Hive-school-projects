/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:22:15 by bposa             #+#    #+#             */
/*   Updated: 2025/02/18 16:24:10 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include <iostream>
#include <string>
#include "Animal.hpp"

using std::string;
using std::cout;
using std::endl;

class Dog : public Animal
{
public:
	Dog();
	Dog(const Dog& obj);
	Dog&	operator=(const Dog& obj);
	~Dog();

	void	makeSound() const override;
};

#endif
