/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:41:21 by bposa             #+#    #+#             */
/*   Updated: 2025/03/21 18:10:07 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

/*	Orthodox Canonical Form	*/
ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137), _target("default") {
	cout << "Shrub. def. constructor" << endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& obj) : AForm(obj), _target(obj._target) {
	cout << "Shrub. copy constructor" << endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	cout << "Shrub. def. destructor" << endl;
}




/*	Overload	*/
ShrubberyCreationForm::ShrubberyCreationForm(const string& target) : AForm("ShrubberyCreationForm", 145, 137), _target(target) {
	cout << "Shrub. overloaded constructor" << endl;
}




/*	Methods	(member functions)	*/
void	ShrubberyCreationForm::act() const {
	cout << "acting." << endl;
}
