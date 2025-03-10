/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:35:34 by bposa             #+#    #+#             */
/*   Updated: 2025/03/10 15:44:37 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>
#include <string>
#include "Bureaucrat.hpp"

using std::cout;
using std::endl;
using std::string;

class Form {
	const string	_name;
	bool			_signed;
	const int		_signGrade;
	const int		_execGrade;
public:
	Form();
	Form(std::string name, int signGrade, int execGrade);
	Form(Form const &src);
	~Form() = default;

	Form &operator=(Form const &src);

	string getName() const;
	bool getSigned() const;
	int getSignGrade() const;
	int getExecGrade() const;

	void beSigned(Bureaucrat &bureaucrat);

	class GradeTooHighException : public std::exception {
	public:
		virtual const char *what() const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		virtual const char *what() const throw();
	};
}

std::ostream& operator<<(std::ostream& os, const Form& obj);

#endif
