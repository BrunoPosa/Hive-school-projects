/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:06:55 by bposa             #+#    #+#             */
/*   Updated: 2025/02/23 21:08:41 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

/*	Orthodox Canonical Form members	*/

Brain::Brain() {
	cout << "Brain def. constructor." << endl;
}

Brain::Brain(const Brain& obj) {
	cout << "Brain copy constructor." << endl;
}

Brain&	Brain::operator=(const Brain& obj) {
	if (this != &obj) {
		cout << "Brain copy assignment." << endl;
	}
	return *this;
}

Brain::~Brain() {	cout << "Brain def. destructor." << endl;	}
