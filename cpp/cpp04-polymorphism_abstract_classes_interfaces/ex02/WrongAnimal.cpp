/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:20:32 by bposa             #+#    #+#             */
/*   Updated: 2025/02/23 20:16:09 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "WrongAnimal.hpp"

/*	Orthodox Canonical Form members	*/

WrongAnimal::WrongAnimal() : _type("WrongAnimalia") {
	cout << "WrongAnimal def. constructor." << endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& obj) : _type(obj._type) {
	cout << "WrongAnimal copy constructor." << endl;
}

WrongAnimal&	WrongAnimal::operator=(const WrongAnimal& obj) {
	if (this != &obj) {
		_type = obj._type;
		cout << "WrongAnimal copy assignment." << endl;
	}
	return *this;
}

WrongAnimal::~WrongAnimal() {	cout << "WrongAnimal def. destructor." << endl;	}



/*	Member functions	*/

void	WrongAnimal::makeSound() const {	cout << "\033[33m" << "*Wild WrongAnimal sound!*" << "\033[0m" << endl;	}   

string	WrongAnimal::getType() const {	return _type;	}
