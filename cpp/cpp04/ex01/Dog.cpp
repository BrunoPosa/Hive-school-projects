/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:07:48 by bposa             #+#    #+#             */
/*   Updated: 2025/02/23 20:18:31 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"

/*	Orthodox Canonical Form members	*/

Dog::Dog() {
	_type = "Dog";
	cout << "Dog def. constructor." << endl;
}

Dog::Dog(const Dog& obj) : Animal(obj) {
	cout << "Dog copy constructor." << endl;
}

Dog&	Dog::operator=(const Dog& obj) {
	if (this != &obj) {
		Animal::operator=(obj);
		cout << "Dog copy assignment." << endl;
	}
	return *this;
}

Dog::~Dog() {
	cout << "Dog destructor called" << endl;
}



/*	Member functions	*/

void Dog::makeSound() const {
	cout << "\033[33m" << this->_type << "*Barkie barks bark*" << "\033[0m" << endl;
}
