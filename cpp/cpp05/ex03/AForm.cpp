/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:44:49 by bposa             #+#    #+#             */
/*   Updated: 2025/03/18 11:58:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

using std::cout;
using std::endl;
using std::string;

/*	Orthodox Canonical Form	*/
AForm::AForm() : _name("default"), _signed(false), _signGrade(1), _execGrade(1) {
	cout << "Aform def. constructor" << endl;
}

AForm::AForm(const AForm& obj)	: _name(obj._name), _signed(obj._signed), _signGrade(obj._signGrade), _execGrade(obj._execGrade) {
	cout << "Aform copy constructor" << endl;
}

AForm&	AForm::operator=(AForm const &obj) {
	if (this != &obj) {
		_signed = obj._signed;
		cout << "Aform copy assignment operator." << endl;
	}
	return *this;
}

AForm::~AForm() {	cout << "Aform def. destructor" << endl;	}




/*	Constructor Overload	*/
AForm::AForm(const string& name, long long signGrade, long long execGrade)
	: _name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade) {
	if (signGrade < _bestGrade || execGrade < _bestGrade) {
		throw GradeTooHighException();
	}
	else if (signGrade > _worstGrade || execGrade > _worstGrade) {
		throw GradeTooLowException();
	}
	cout << "Aform overloaded constructor" << endl;
}




/*	Member Functions	*/

const string&	AForm::getName()		const noexcept {	return _name;	}
bool			AForm::getSigned()		const noexcept {	return _signed;	}
unsigned short	AForm::getSignGrade()	const noexcept {	return _signGrade;	}
unsigned short	AForm::getExecGrade()	const noexcept {	return _execGrade;	}

void	AForm::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > _signGrade) {
		throw GradeTooLowException();
	}
	_signed = true;
}

bool	AForm::execute(Bureaucrat const &executor)	const {
	if (!_signed) {
		throw FormNotSignedException();
	}
	if (executor.getGrade() > _execGrade) {
		throw GradeTooLowException();
	}
	return (this->act());
}

const char*	AForm::GradeTooHighException::what()	const noexcept {	return "~Signer's grade too high!";	}
const char*	AForm::GradeTooLowException::what()		const noexcept {	return "~Signer's grade too low!";	}
const char*	AForm::FormNotSignedException::what()	const noexcept {	return "~Form must be signed to execute it!";	}




/*	Insertion operator overload	*/
std::ostream&	operator<<(std::ostream& os, const AForm& obj) {
	return os
		<< "Form: " << obj.getName() << ", "
		<< "Sign Grade: " << obj.getSignGrade() << ", "
		<< "Execution Grade: " << obj.getExecGrade() << ", "
		<< "Signed: " << obj.getSigned()
		<< endl;
}
