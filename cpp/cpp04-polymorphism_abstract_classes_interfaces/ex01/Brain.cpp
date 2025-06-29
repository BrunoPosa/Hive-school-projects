/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:06:55 by bposa             #+#    #+#             */
/*   Updated: 2025/03/02 19:15:01 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

/*	Orthodox Canonical Form members	*/

Brain::Brain() : _index(0) {
	cout << "Brain def. constructor." << endl;
}

Brain::Brain(const Brain& obj) : _index(obj._index) {
	for (int i = 0; i < BRAINSIZE; i++) {
		_ideas[i] = obj._ideas[i];
	}
	cout << "Brain copy constructor." << endl;
}

Brain&	Brain::operator=(const Brain& obj) {
	if (this != &obj) {
		_index = obj._index;
		for (unsigned int i = 0; i < BRAINSIZE; i++) {
			_ideas[i] = obj._ideas[i];
		}
		cout << "Brain copy assignment." << endl;
	}
	return *this;
}

Brain::~Brain() {	cout << "Brain def. destructor." << endl;	}



/*	Member functions	*/

void	Brain::printAll() const {
	for(int i = 0; i < BRAINSIZE ; i++) {
		if (_ideas[i].empty() == false) {
			cout << "-" << _ideas[i] << endl;
		}
	}
}

void	Brain::addIdea(const string& newIdea)
{
	if (_index == BRAINSIZE)
		_index = 0;
	_ideas[_index] = newIdea;
	_index++;
}
