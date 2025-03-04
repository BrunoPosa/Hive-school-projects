/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:04:16 by bposa             #+#    #+#             */
/*   Updated: 2025/03/04 22:19:28 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Bureaucrat {
	const string	_name;
	unsigned int	_grade;

public:
	const string&	getName() const;
	unsigned int	getGrade() const;
	void	upGrade();//grade 3 becomes grade 2
	void	downGrade();
};

#endif
