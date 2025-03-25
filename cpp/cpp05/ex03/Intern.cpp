/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:01:38 by bposa             #+#    #+#             */
/*   Updated: 2025/03/25 17:00:05 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

AForm*	Intern::_createShrubberyForm(const string& _target) {	return new ShrubberyCreationForm(_target);	}
AForm*	Intern::_createRobotomyForm(const string& _target) {	return new ShrubberyCreationForm(_target);	}
AForm*	Intern::_createPresidentialForm(const string& _target) {	return new ShrubberyCreationForm(_target);	}

const Intern::_form	Intern::_knownForms[] = {
	{"shrubbery creation",	&Intern::_createShrubberyForm},
	{"robotomy request",	&Intern::_createRobotomyForm},
	{"presidential pardon",	&Intern::_createPresidentialForm}
	// {nullptr, nullptr}
};

string&	Intern::_toLower(string& str) {
	for (char& ch : str) {
		if (ch >= 'A' && ch <= 'Z') {
			ch += ('a' - 'A');
		}
	}
	return str;
}

AForm*	Intern::_makeForm(string& _name, string& _target) {
	_name = _toLower(_name);

	for (const _form& form : _knownForms) {
		if (_name == form._formName) {
			return (this->*form._function)(_target);
		}
	}
	return nullptr;
}

AForm*	Intern::makeForm(string formName, string formTarget) {
	AForm*	result = _makeForm(formName, formTarget);

	if (result == nullptr) {
		cout << "Intern can't find the specified form!" << endl;
	} else {
		cout << "Intern created " << _toLower(formName) << " form." << endl;
	}

	return result;
}
