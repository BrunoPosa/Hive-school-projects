/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:02:29 by bposa             #+#    #+#             */
/*   Updated: 2025/03/24 18:10:13 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include <iostream>
#include "AForm.hpp"


using std::cout;
using std::endl;
using std::string;

class PresidentialPardonForm : public AForm {
	string	_target;
public:
	PresidentialPardonForm();
	PresidentialPardonForm(const PresidentialPardonForm& obj);
	PresidentialPardonForm&	operator=(const PresidentialPardonForm& obj)	= delete;
	~PresidentialPardonForm();
	PresidentialPardonForm(const string& target);

	bool	act() const override;
};

#endif
