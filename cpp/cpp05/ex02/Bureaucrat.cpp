/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:09:06 by bposa             #+#    #+#             */
/*   Updated: 2025/03/28 15:24:35 by bposa            ###   ########.fr       */
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

void	Bureaucrat::signForm(AForm& obj) const {
	try {
		obj.beSigned(*this);
	}
	catch (AForm::GradeTooLowException& e) {
		cout << YELLOWISH << _name << " cannot sign " << obj.getName() << " because " << e.what() << RESETISH << endl;
		return;
	}
	cout << YELLOWISH << _name << " signed " << obj.getName() << RESETISH << endl;
}

bool	Bureaucrat::executeForm(AForm const & form) {
	try {
		if (form.execute(*this) == false) {
			cout << REDISH << _name << " failed to execute " << form.getName() << " due to an error." << RESETISH << endl;
		}
	} catch (std::exception& e) {
		cout << YELLOWISH << _name << " could not execute form because of: " << e.what() << RESETISH << endl;
		return false;
	}
	cout << YELLOWISH << _name << " executed " << form.getName() << RESETISH << endl;
	return true;
}


const char*	Bureaucrat::GradeTooHighException::what() const noexcept {	return "~Grade too high!";	}

const char*	Bureaucrat::GradeTooLowException::what() const noexcept {	return "~Grade too low!";	}



/*	Insertion operator overload	*/
std::ostream&	operator<<(std::ostream& os, const Bureaucrat& obj) {
	return os << YELLOWISH
		<< "AForm " << obj.getName() << "" << obj.getGrade()
		<< RESETISH << endl;
}
