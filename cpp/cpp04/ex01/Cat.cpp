/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:26:41 by bposa             #+#    #+#             */
/*   Updated: 2025/02/23 20:18:49 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Animal.hpp"

/*	Orthodox Canonical Form members	*/

Cat::Cat() {
	_type = "Cat";
	cout << "Cat def. constructor." << endl;
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
	cout << "Cat destructor called" << endl;
}



/*	Member functions	*/

void Cat::makeSound() const {
	cout << "\033[33m" << this->_type << "*Meowy kitty purr*" << "\033[0m" << endl;
}
