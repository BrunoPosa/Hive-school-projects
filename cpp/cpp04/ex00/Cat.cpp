/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:26:41 by bposa             #+#    #+#             */
/*   Updated: 2025/02/18 16:37:24 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Animal.hpp"

/*	Orthodox Canonical Form members	*/

Cat::Cat() {
	_type = "Cat";
	cout << "Cat constructor." << endl;
}

Cat::Cat(const Cat& obj) : Animal(obj) {
	cout << "Cat copy constructor." << endl;
}

Cat&	Cat::operator=(const Cat& obj) {
	if (this != &obj) {
		Animal::operator=(obj);
		cout << "Cat copy assignment." << endl;
	}
	return *this;
}

Cat::~Cat() {
	std::cout << "Cat destructor called" << std::endl;
}



/*	Member functions	*/

void Cat::makeSound() const {
	cout << this->_type << "*Meowy kitty purr*" << endl;
}
