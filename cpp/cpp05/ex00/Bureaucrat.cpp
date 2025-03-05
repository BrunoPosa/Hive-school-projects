/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:09:06 by bposa             #+#    #+#             */
/*   Updated: 2025/03/05 22:11:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

/*	Default Constructor	*/
Bureaucrat::Bureaucrat() : _name("JohnDoe"), _grade(150) {}



/*	Constructor Overload	*/
Bureaucrat::Bureaucrat(const string& name, unsigned short grade) : _name(name), _grade(grade) {
	_gradeChecker(_grade);
}



/*	Member Functions	*/

void	Bureaucrat::_gradeChecker(long grade) {
	if (grade < _bestGrade) {
		throw GradeTooHighException();
	}
	else if (grade > _worstGrade) {
		throw GradeTooLowException();
	}
}

const string&	Bureaucrat::getName() const {	return _name;	}

unsigned int	Bureaucrat::getGrade() const {	return _grade;	}

void	Bureaucrat::upGrade() {
	_gradeChecker(_grade - _gradeStep);
	_grade -= _gradeStep;
}

void	Bureaucrat::downGrade() {
	_gradeChecker(_grade + _gradeStep);
	_grade += _gradeStep;
}

const char*	Bureaucrat::GradeTooHighException::what() const throw() {	return "Grade too high!";	}

const char*	Bureaucrat::GradeTooLowException::what() const throw() {	return "Grade too low!";	}



/*	Insertion operator overload	*/
std::ostream&	operator<<(std::ostream& os, const Bureaucrat& obj) {
	return os << obj.getName() << ", bureaucrat grade " << obj.getGrade() << endl;
}
