/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:30:44 by bposa             #+#    #+#             */
/*   Updated: 2025/03/02 21:27:59 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

/*	Orthodox Canonical Form members	*/

Animal::Animal() : _type("Animalia") {
	cout << "Animal def. constructor." << endl;
}

Animal::Animal(const Animal& obj) : _type(obj._type) {
	cout << "Animal copy constructor." << endl;
}

Animal&	Animal::operator=(const Animal& obj) {
	if (this != &obj) {
		_type = obj._type;
		cout << "Animal copy assignment." << endl;
	}
	return *this;
}

Animal::~Animal() {	cout << "Animal def. destructor." << endl;	}



/*	Member functions	*/

void	Animal::makeSound() const {	cout << "\033[33m" << "*Wild Animal sound!*" << "\033[0m" << endl;	}   

string	Animal::getType() const {	return _type;	}
