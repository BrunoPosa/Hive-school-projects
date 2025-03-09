/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:04:16 by bposa             #+#    #+#             */
/*   Updated: 2025/03/10 00:01:55 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>
#include "Colors.hpp"

using std::cout;
using std::endl;
using std::string;

/**
 *	Default constructor sets _name to 'JohnDoe' and _grade to worst grade.
 *	Best grade is 1, worst 150;
 *	upGrade() decrements _grade and downGrade() increments it.
 *
 *	Special exceptions: GradeTooHighException and GradeTooLowException.
 */
class Bureaucrat {
	const string				_name;
	unsigned short				_grade;
	static const unsigned short	_bestGrade	= 1;
	static const unsigned short	_worstGrade	= 150;
	static_assert(_bestGrade < _worstGrade, "Best grade must be less than worst grade");

public:
	Bureaucrat();
	Bureaucrat(const Bureaucrat& obj);
	Bureaucrat&	operator=(const Bureaucrat& obj);
	~Bureaucrat() = default;
	Bureaucrat(const string& name, long long grade);

	const string&	getName() const noexcept;
	unsigned int	getGrade() const noexcept;
	void			upGrade();		//--grade (3 becomes 2)
	void			downGrade();	//++grade (3 becomes 4)

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
