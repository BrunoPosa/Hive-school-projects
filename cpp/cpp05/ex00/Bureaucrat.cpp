/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:09:06 by bposa             #+#    #+#             */
/*   Updated: 2025/03/06 18:34:15 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

/*	Orthodox Canonical Form	*/
Bureaucrat::Bureaucrat() : _name("JohnDoe"), _grade(150) {}

Bureaucrat::Bureaucrat(const Bureaucrat& obj) : _name(obj._name), _grade(obj._grade) {}



/*	Constructor Overload	*/
Bureaucrat::Bureaucrat(const string& name, long grade) : _name(name), _grade(grade) {
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
	if (static_cast<long>(_grade) - static_cast<long>(_gradeStep) < _bestGrade) {
		throw GradeTooHighException();
	};
	_grade -= _gradeStep;
}

void	Bureaucrat::downGrade() {
	if (static_cast<long>(_grade) + static_cast<long>(_gradeStep) > _worstGrade) {
		throw GradeTooLowException();
	};
	_grade += _gradeStep;
}

const char*	Bureaucrat::GradeTooHighException::what() const noexcept {	return "Grade too high!";	}

const char*	Bureaucrat::GradeTooLowException::what() const noexcept {	return "Grade too low!";	}



/*	Insertion operator overload	*/
std::ostream&	operator<<(std::ostream& os, const Bureaucrat& obj) {
	return os << getColor(Color::YELLOW)
		<< obj.getName() << ", bureaucrat grade " << obj.getGrade()
		<< getColor(Color::RESET) << endl;
}
