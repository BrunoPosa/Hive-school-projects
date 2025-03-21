/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationAForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:30:25 by bposa             #+#    #+#             */
/*   Updated: 2025/03/18 13:37:26 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>

using std::cout;
using std::endl;
using std::string;

class ShrubberyCreationForm : public AForm {
	string	_target;
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(const ShrubberyCreationForm& obj);
	ShrubberyCreationForm&	operator=(const ShrubberyCreationForm& obj)	= delete;
	~ShrubberyCreationForm();
	ShrubberyCreationForm(const string& target);

	void	act() const override;
};

#endif