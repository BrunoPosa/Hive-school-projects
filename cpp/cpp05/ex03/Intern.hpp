/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:58:01 by bposa             #+#    #+#             */
/*   Updated: 2025/03/25 13:54:19 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <memory>

using std::string;

/*
 *	Interns takes 'shrubbery creation'/'robotomy request'/'presidential pardon'
 *	as form parameter, and makes the corresponding Form, passing it the given target.
 */
class Intern {
	static constexpr unsigned int	_hash(const char *str);
	string&							_toLower(string& str);
	AForm*							_makeForm(string name, string target);
public:
	Intern() = default;
	// Intern(const Intern& obj);
	// Intern&	operator=(const Intern& obj);
	// ~Intern();

	AForm*	makeForm(string formName, string formTarget);
};

#endif