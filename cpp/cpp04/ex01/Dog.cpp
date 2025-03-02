/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:07:48 by bposa             #+#    #+#             */
/*   Updated: 2025/03/02 20:04:30 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"

/*	Orthodox Canonical Form members	*/

Dog::Dog() : _brain(new Brain()) {
	_type = "Dog";
	cout << "Dog def. constructor." << endl;
}

Dog::Dog(const Dog& obj) : Animal(obj), _brain(new Brain(*obj._brain)) {
	cout << "Dog copy constructor." << endl;
}

Dog&	Dog::operator=(const Dog& obj) {
	if (this != &obj) {
		Animal::operator=(obj);
		delete _brain;
		_brain = new Brain(*obj._brain);
		cout << "Dog copy assignment." << endl;
	}
	return *this;
}

Dog::~Dog() {
	cout << "Dog def. destructor." << endl;
	delete _brain;
}



/*	Member functions	*/

void Dog::makeSound() const {
	cout << "\033[33m" << this->_type << "*Barkie barks bark*" << "\033[0m" << endl;
}

void	Dog::addIdea(const string& idea) {	_brain->addIdea(idea);	}

void	Dog::printIdeas() const {
	cout << "\e[32m" << "--Dog ideaz--" << endl;
	_brain->printAll();
	cout << "\e[0m" << endl;
}
