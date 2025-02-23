/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:22:47 by bposa             #+#    #+#             */
/*   Updated: 2025/02/23 18:23:53 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"
#include "WrongAnimal.hpp"

/*	Orthodox Canonical Form members	*/

WrongCat::WrongCat() {
	_type = "WrongCat";
	cout << "WrongCat constructor." << endl;
}

WrongCat::WrongCat(const WrongCat& obj) : WrongAnimal(obj) {
	cout << "WrongCat copy constructor." << endl;
}

WrongCat&	WrongCat::operator=(const WrongCat& obj) {
	if (this != &obj) {
		WrongAnimal::operator=(obj);
		cout << "WrongCat copy assignment." << endl;
	}
	return *this;
}

WrongCat::~WrongCat() {
	std::cout << "WrongCat destructor called" << std::endl;
}



/*	Member functions	*/

void WrongCat::makeSound() const {
	cout << this->_type << "*Meowy kitty purr*" << endl;
}
