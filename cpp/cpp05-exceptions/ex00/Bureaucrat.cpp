/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:09:06 by bposa             #+#    #+#             */
/*   Updated: 2025/03/28 19:10:05 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

using std::cout;
using std::endl;
using std::string;

/*	Orthodox Canonical Form	*/
Bureaucrat::Bureaucrat() : _name("JohnDoe"), _grade(150) {}

Bureaucrat::Bureaucrat(const Bureaucrat& obj) : _name(obj._name), _grade(obj._grade) {}

Bureaucrat&	Bureaucrat::operator=(const Bureaucrat& obj) {
	if (this != &obj) {
		_grade = obj._grade;
	}
	return *this;
}

Bureaucrat::~Bureaucrat() {}



/*	Constructor Overload	*/
Bureaucrat::Bureaucrat(const string& name, unsigned short grade) : _name(name), _grade(grade) {
	if (grade < _bestGrade) {
		throw GradeTooHighException();
	}
	else if (grade > _worstGrade) {
		throw GradeTooLowException();
	}
}



/*	Member Functions	*/

const string&	Bureaucrat::getName() const noexcept {	return _name;	}

unsigned int	Bureaucrat::getGrade() const noexcept {	return _grade;	}

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

const char*	Bureaucrat::GradeTooHighException::what() const noexcept {	return "Grade too high!";	}

const char*	Bureaucrat::GradeTooLowException::what() const noexcept {	return "Grade too low!";	}



/*	Insertion operator overload	*/
std::ostream&	operator<<(std::ostream& os, const Bureaucrat& obj) {
	return os << YELLOWISH
		<< obj.getName() << ", bureaucrat grade " << obj.getGrade()
		<< RESETISH << endl;
}
