/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:22:15 by bposa             #+#    #+#             */
/*   Updated: 2025/02/17 19:45:23 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class Dog : Animal
{
public:
	Dog();
	Dog(const Dog& obj);
	~Dog();
	void	makeSound() override;
};

#endif
