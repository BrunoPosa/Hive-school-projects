/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:25:31 by bposa             #+#    #+#             */
/*   Updated: 2025/01/15 02:20:21 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_CLASS_HPP
# define PHONEBOOK_CLASS_HPP

#include "Contact.class.hpp"

/* Limits */
# define PB_SIZE 10
# define PB_INPUTSTR_MAX 512
# define PB_ATTEMPT_MAX 3

/* Colors */
# define PB_YELLOW "\033[33m"
# define PB_GREEN "\e[1;32m"
# define PB_RESET_COLOR "\033[0m"

class PhoneBook
{
	public:
		PhoneBook();

		bool			addContact(void);
		bool			search(void);
		unsigned int	getSize(void);


	private:
		Contact			_contacts[PB_SIZE];
		unsigned int	_index;
		unsigned int	_size;

		bool			_addField(std::string& field, const std::string& label);
		unsigned int	_toIndex(void);
		bool			_isAllDigits(const std::string& inputStr);
		bool			_isValidNumber(const std::string& inputStr, unsigned int& selection);
		bool			_inputFromStdin(std::string& inputStr);
};

#endif