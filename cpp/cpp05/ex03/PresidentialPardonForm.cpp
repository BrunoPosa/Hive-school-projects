/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:05:46 by bposa             #+#    #+#             */
/*   Updated: 2025/03/27 17:35:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

using std::cout;
using std::endl;
using std::string;

/*	Orthodox Canonical Form	*/
PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5), _target("default") {
	cout << "Presidential def. constructor" << endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& obj) : AForm(obj), _target(obj._target) {
	cout << "Presidential copy constructor" << endl;
}

PresidentialPardonForm&	PresidentialPardonForm::operator=(const PresidentialPardonForm& obj) {
	if (this != &obj) {
		_target = obj._target;
		cout << "Presidential copy assignment" << endl;
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {
	cout << "Presidential def. destructor" << endl;
}




/*	Overload	*/
PresidentialPardonForm::PresidentialPardonForm(const string& target) : AForm("PresidentialPardonForm", 25, 5), _target(target) {
	cout << "Presidential overloaded constructor" << endl;
}




/*	Methods	(member functions)	*/
bool	PresidentialPardonForm::act() const {
	cout << YELLOWISH << _target << " has been pardoned by Zaphod Beeblebrox" << RESETISH << endl;
	return true;
}