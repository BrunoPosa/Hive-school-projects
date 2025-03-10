/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:44:49 by bposa             #+#    #+#             */
/*   Updated: 2025/03/10 15:50:03 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form() : _name("JohnDoe"), _signed(false), _signGrade(1), _execGrade(1) {}









/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:09:06 by bposa             #+#    #+#             */
/*   Updated: 2025/03/10 00:40:36 by bposa            ###   ########.fr       */
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
std::ostream&	operator<<(std::ostream& os, const Form& obj) {
	return os << MyColor::YELLOW
		<< obj.getName() << ", bureaucrat grade " << obj.getGrade()
		<< MyColor::RESET << endl;
}
