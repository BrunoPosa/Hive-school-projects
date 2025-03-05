/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:04:16 by bposa             #+#    #+#             */
/*   Updated: 2025/03/05 22:11:45 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>

using std::cout;
using std::endl;
using std::string;

/**
 *	Default constructor sets _name to 'JohnDoe' and _grade to worst grade.
 *	Best grade is 1, worst 150; upGrade(){--_grade} and downGrade(){++_grade}.
 *	Throwable exceptions: GradeTooHighException and GradeTooLowException.
 */
class Bureaucrat {
	const string				_name;
	unsigned short				_grade;
	static const unsigned short	_bestGrade	= 100;
	static const unsigned short	_worstGrade	= 150;
	static const unsigned short	_gradeStep	= 1;
	static_assert(_bestGrade < _worstGrade, "Best grade must be less than worst grade");
	void						_gradeChecker(long grade);

public:
	Bureaucrat();
	Bureaucrat(const Bureaucrat& obj)				= delete;
	Bureaucrat&	operator=(const Bureaucrat& obj)	= delete;
	~Bureaucrat()									= default;
	Bureaucrat(const string& name, unsigned short grade);

	const string&	getName() const;
	unsigned int	getGrade() const;
	void			upGrade();//--grade (3 becomes 2)
	void			downGrade();//++grade (3 becomes 4)

	class GradeTooHighException : public std::exception {
	public:
		const char* what() const noexcept override;
	};
	class GradeTooLowException : public std::exception {
	public:
		const char* what() const noexcept override;
	};
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj);

#endif
