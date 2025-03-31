/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:01:38 by bposa             #+#    #+#             */
/*   Updated: 2025/03/31 17:08:34 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

using std::string;
using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;

/*	Orthodox Canonical Form	*/

Intern::Intern() {	cout << "Intern def. constructor" << endl;	}
Intern::Intern(const Intern& obj) {
	(void)obj;
	cout << "Intern copy constructor" << endl;
}
Intern&	Intern::operator=(const Intern& obj) {
	(void)obj;
	cout << "Intern copy assignment" << endl;
	return *this;
}
Intern::~Intern() {	cout << "Intern def. destructor" << endl;	}




const Intern::_form	Intern::_knownForms[] = {
	{"shrubbery creation",	&Intern::_createShrubberyForm},
	{"robotomy request",	&Intern::_createRobotomyForm},
	{"presidential pardon",	&Intern::_createPresidentialForm}
};




/*	Member Functions	*/

unique_ptr<AForm>	Intern::_createShrubberyForm(const string& _target) 	{ return make_unique<ShrubberyCreationForm>(_target); }
unique_ptr<AForm>	Intern::_createRobotomyForm(const string& _target) 		{ return make_unique<RobotomyRequestForm>(_target); }
unique_ptr<AForm>	Intern::_createPresidentialForm(const string& _target)	{ return make_unique<PresidentialPardonForm>(_target); }

string&	Intern::_toLower(string& str) {
	for (char& ch : str) {
		if (ch >= 'A' && ch <= 'Z') {
			ch += ('a' - 'A');
		}
	}
	return str;
}

std::unique_ptr<AForm>	Intern::_makeForm(string& _name, string& _target) {
	_name = _toLower(_name);

	for (const _form& form : _knownForms) {
		if (_name == form._formName) {
			return (this->*form._function)(_target);
		}
	}
	return nullptr;
}

unique_ptr<AForm>	Intern::makeForm(string formName, string formTarget) {
	unique_ptr<AForm>result = _makeForm(formName, formTarget);

	if (result == nullptr) {
		cout << "The intern doesn't know anything about '" << formName << "' form!" << endl;
	} else {
		cout << YELLOWISH << "Intern created " << _toLower(formName) << " form." << RESETISH << endl;
	}

	return result;
}
