/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:41:21 by bposa             #+#    #+#             */
/*   Updated: 2025/03/24 19:46:56 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

/*	Orthodox Canonical Form	*/
ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137), _target("default") {
	cout << "Shrubbery def. constructor" << endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& obj) : AForm(obj), _target(obj._target) {
	cout << "Shrubbery copy constructor" << endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	cout << "Shrubbery def. destructor" << endl;
}




/*	Overload	*/
ShrubberyCreationForm::ShrubberyCreationForm(const string& target) : AForm("ShrubberyCreationForm", 145, 137), _target(target) {
	cout << "Shrubbery overloaded constructor" << endl;
}




/*	Methods	(member functions)	*/
bool	ShrubberyCreationForm::act() const {
	std::ofstream outFile(_target + "_shrubbery", std::ios::out | std::ios::trunc);
	if (!outFile.is_open()) {
		cout << "Could not open file!" << endl;
		return false;
	}

	int	i = _target.length();
	do {
		outFile << R"(
			# #### ####
		### \/#|### |/####
		##\/#/ \||/##/_/##/_#
		###  \/###|/ \/ # ###
	##_\_#\_\## | #/###_/_####
	## #### # \ #| /  #### ##/##
	__#_--###`  |{,###---###-~
				\ }{
				}}{
				}}{
			ejm  {{}
		, -=-~{ .-^- _
				`}
				{)";
	} while (--i > 0);

	if (outFile.fail()) {
		cout << "Writing failed!" << endl;
		return false;
	}
	outFile.close();

	cout << GREENISH << "Shrubbery planted in " << _target << "_shrubbery." << RESETISH << endl;
	return true;
}
