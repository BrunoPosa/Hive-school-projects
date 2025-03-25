/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:01:38 by bposa             #+#    #+#             */
/*   Updated: 2025/03/25 13:56:40 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

unsigned int	Intern::_hash(const char *str) {
	unsigned int	hash = 0;
	while (*str) {
		hash = hash * 31 + *str++;
	}
	return hash;
}

string&	Intern::_toLower(string& str) {
	for (char& ch : str) {
		if (ch >= 'A' && ch <= 'Z') {
			ch += ('a' - 'A');
		}
	}
	return str;
}

AForm*	Intern::_makeForm(string name, string target) {

	name = _toLower(name);

	switch (_hash(name.c_str()))
	{
		case _hash("shrubbery creation"):
			return new ShrubberyCreationForm(target);
		case _hash("robotomy request"):
			return new RobotomyRequestForm(target);
		case _hash("presidential pardon"):
			return new PresidentialPardonForm(target);
		default:
			return nullptr;
	}
	cout << "Intern created " << name << " form." << endl;
}


AForm*	Intern::makeForm(string formName, string formTarget) {

	AForm*	result = _makeForm(formName, formTarget);

	if (result == nullptr) {
		cout << "Intern can't find the specified form!" << endl;
	} else {
		cout << "Intern created " << formName << " form." << endl;
	}

	return result;
}
