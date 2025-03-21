/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:09:06 by bposa             #+#    #+#             */
/*   Updated: 2025/03/21 15:27:15 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

/*	Orthodox Canonical Form	*/
Bureaucrat::Bureaucrat() : _name("JohnDoe"), _grade(150) {}

Bureaucrat::Bureaucrat(const Bureaucrat& obj) : _name(obj._name), _grade(obj._grade) {}

Bureaucrat&	Bureaucrat::operator=(const Bureaucrat& obj) {
	if (this != &obj) {
		_grade = obj._grade;
	}
	return *this;
}



/*	Constructor Overload	*/
Bureaucrat::Bureaucrat(const string& name, long long grade) : _name(name), _grade(grade) {
	if (grade < _bestGrade) {
		throw GradeTooHighException();
	}
	else if (grade > _worstGrade) {
		throw GradeTooLowException();
	}
}



/*	Member Functions	*/

const string&	Bureaucrat::getName() const noexcept {	return _name;	}

unsigned short	Bureaucrat::getGrade() const noexcept {	return _grade;	}

void	Bureaucrat::upGrade() {
	if (_grade == _bestGrade) {
		throw GradeTooHighException();
	};
	--_grade;
}

void	Bureaucrat::downGrade() {
	if (_grade == _worstGrade) {
		throw GradeTooLowException();
	};
	++_grade;
}

void	Bureaucrat::signAForm(AForm& obj) const {
	try {
		obj.beSigned(*this);
	}
	catch (AForm::GradeTooLowException& e) {
		cout << YELLOWISH << _name << " cannot sign " << obj.getName() << " because " << e.what() << RESETISH << endl;
		return;
	}
	cout << YELLOWISH << _name << " signed " << obj.getName() << RESETISH << endl;
}

const char*	Bureaucrat::GradeTooHighException::what() const noexcept {	return "Grade too high!";	}

const char*	Bureaucrat::GradeTooLowException::what() const noexcept {	return "Grade too low!";	}



/*	Insertion operator overload	*/
std::ostream&	operator<<(std::ostream& os, const Bureaucrat& obj) {
	return os << YELLOWISH
		<< "AForm " << obj.getName() << "" << obj.getGrade()
		<< RESETISH << endl;
}
