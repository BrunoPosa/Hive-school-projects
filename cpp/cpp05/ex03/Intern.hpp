/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:58:01 by bposa             #+#    #+#             */
/*   Updated: 2025/03/27 17:28:28 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

#include <new>
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

/*
 *	Interns takes 'shrubbery creation'/'robotomy request'/'presidential pardon'
 *	as form parameter, and returns the corresponding heap allocated Form with given target.
 */
class Intern {
	AForm*	_createShrubberyForm(const std::string& _target);
	AForm*	_createRobotomyForm(const std::string& _target);
	AForm*	_createPresidentialForm(const std::string& _target);
	struct _form {
		std::string	_formName;
		AForm* (Intern::*_function)(const std::string&);
	};
	static const _form	_knownForms[];

	std::string&	_toLower(std::string& str);
	AForm*	_makeForm(std::string& name, std::string& target);

public:
	Intern();
	Intern(const Intern& obj);
	Intern&	operator=(const Intern& obj);
	~Intern();

	AForm*	makeForm(std::string formName, std::string formTarget);
};

#endif
