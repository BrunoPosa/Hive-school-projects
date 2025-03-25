/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:58:01 by bposa             #+#    #+#             */
/*   Updated: 2025/03/25 17:38:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

using std::string;

/*
 *	Interns takes 'shrubbery creation'/'robotomy request'/'presidential pardon'
 *	as form parameter, and returns the corresponding heap allocated Form with given target.
 */
class Intern {
	struct _form {
		string	_formName;
		AForm* (Intern::*_function)(const string&);
	};
	static const _form	_knownForms[];

	string&	_toLower(string& str);
	AForm*	_makeForm(string& name, string& target);

	AForm*	_createShrubberyForm(const string& _target);
	AForm*	_createRobotomyForm(const string& _target);
	AForm*	_createPresidentialForm(const string& _target);

public:
	Intern() = default;
	Intern(const Intern& obj) = default;
	Intern&	operator=(const Intern& obj) = default;
	~Intern() = default;

	AForm*	makeForm(string formName, string formTarget);
	void	print();
};

#endif