/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:30:11 by bposa             #+#    #+#             */
/*   Updated: 2025/03/25 17:19:50 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

/*	Orthodox Canonical Form	*/
RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45), _target("_empty_") {
	cout << "Robotomy def. constructor" << endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& obj) : AForm(obj), _target(obj._target) {
	cout << "Robotomy copy constructor" << endl;
}

RobotomyRequestForm::~RobotomyRequestForm() {
	cout << "Robotomy def. destructor" << endl;
}




/*	Overload	*/
RobotomyRequestForm::RobotomyRequestForm(const string& target) : AForm("RobotomyRequestForm", 72, 45), _target(target) {
	cout << "Robotomy overloaded constructor." << endl;
}




/*	Methods	*/
bool	RobotomyRequestForm::act() const {
	cout << "~~~ drill sOouund.. ~~~" << endl;

	std::srand(std::time(nullptr));
	if (std::rand() & 1) {
		cout << GREENISH << _target << " has been robotomized successfully!" << RESETISH << endl;
	} else {
		cout << REDISH << "Robotomy failed, " << _target << " is stil hooman." << RESETISH << endl;
	}

	return true;
}
