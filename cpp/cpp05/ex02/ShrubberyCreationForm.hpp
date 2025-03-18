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

#ifndef SHRUBBERYCREATIONAForm_HPP
# define SHRUBBERYCREATIONAForm_HPP

#include "AForm.hpp"
#include <fstream>

using std::cout;
using std::endl;
using std::string;

class ShrubberyCreationForm : public AForm {
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(string);
	ShrubberyCreationForm(const ShrubberyCreationForm&);
	ShrubberyCreationForm&	operator=(const ShrubberyCreationForm&);
	~ShrubberyCreationForm();// override;
};

#endif