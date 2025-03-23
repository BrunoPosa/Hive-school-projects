/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:30:11 by bposa             #+#    #+#             */
/*   Updated: 2025/03/23 19:56:36 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "AForm.hpp"

using std::cout;
using std::endl;
using std::string;

class RobotomyRequestForm : public AForm {
	string	_target;
public:
	RobotomyRequestForm();
	RobotomyRequestForm(const RobotomyRequestForm& obj);
	RobotomyRequestForm&	operator=(const RobotomyRequestForm& obj)	= delete;
	~RobotomyRequestForm();
	RobotomyRequestForm(const string& target);

	bool	act() const override;
};

#endif