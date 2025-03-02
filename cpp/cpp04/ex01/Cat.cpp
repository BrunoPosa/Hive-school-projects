/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:26:41 by bposa             #+#    #+#             */
/*   Updated: 2025/03/02 20:33:51 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Animal.hpp"

/*	Orthodox Canonical Form members	*/

Cat::Cat() : _brain(new Brain()) {
	_type = "Cat";
	cout << "Cat def. constructor." << endl;
}

Cat::Cat(const Cat& obj) : Animal(obj), _brain(new Brain(*obj._brain)) {
	cout << "Cat copy constructor." << endl;
}

Cat&	Cat::operator=(const Cat& obj) {
	if (this != &obj) {
		Animal::operator=(obj);
		delete _brain;
		_brain = new Brain(*obj._brain);
		cout << "Cat copy assignment." << endl;
	}
	return *this;
}

Cat::~Cat() {
	cout << "Cat def. destructor." << endl;
	delete _brain;
}



/*	Member functions	*/

void Cat::makeSound() const {
	cout << "\033[33m" << this->_type << "*Meowy kitty purr*" << "\033[0m" << endl;
}

void	Cat::addIdea(const string& idea) {	_brain->addIdea(idea);	}

void	Cat::printIdeas() const {
	cout << "\e[95m" << "--Cat ideaz--" << endl;
	_brain->printAll();
	cout << "\e[0m" << endl;
}
