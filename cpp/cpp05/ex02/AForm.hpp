/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:35:34 by bposa             #+#    #+#             */
/*   Updated: 2025/03/24 18:14:20 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AForm_HPP
# define AForm_HPP

#include <iostream>
#include <string>
#include <exception>
#include "Bureaucrat.hpp"

using std::cout;
using std::endl;
using std::string;

class Bureaucrat; //Forward declaration to avoid circular dependency

/*
 *	execute() method throws exceptions in case of too low/high grade Bureaucrat,
 *	and returns 'false' on failure during execution (e.g. writing to file or making sound)
*/
class AForm {
	static const unsigned short	_bestGrade	= 1;
	static const unsigned short	_worstGrade	= 150;
	static_assert(_bestGrade < _worstGrade, "Best grade must be less than worst grade");//delete for production code
	
	const string			_name;
	bool					_signed;
	const unsigned short	_signGrade;
	const unsigned short	_execGrade;

public:
	AForm();
	AForm(AForm const &obj);
	AForm&	operator=(AForm const &src)	= delete;
	virtual ~AForm();
	AForm(const string& name, long long signGrade, long long execGrade);

	const string&	getName()		const noexcept;
	bool			getSigned()		const noexcept;
	unsigned short	getSignGrade()	const noexcept;
	unsigned short	getExecGrade()	const noexcept;
	void			beSigned(Bureaucrat const &bureaucrat);
	bool			execute(Bureaucrat const &executor)	const;
	virtual bool	act() const		= 0;



	class GradeTooHighException : public std::exception {
	public:
		virtual const char *what() const throw();
	};
	class GradeTooLowException : public std::exception {
	public:
		virtual const char *what() const throw();
	};
	class FormNotSignedException : public std::exception {
	public:
		virtual const char *what() const throw();
	};
};


std::ostream& operator<<(std::ostream& os, const AForm& obj);

#endif
