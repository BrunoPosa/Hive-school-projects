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

#pragma once
#include "Contact.class.hpp"

/* Between 1 and UNSIGNED_INT_MAX (or smaller number depending on system) */
#ifndef PHONEBOOK_SIZE
# define PHONEBOOK_SIZE 3
#endif

#ifndef MAIN_INPUT_BUFFER_SIZE
# define MAIN_INPUT_BUFFER_SIZE 1024
#endif

#ifndef MAIN_TRIES_MAX
# define MAIN_TRIES_MAX 3
#endif

#ifndef YELLOW_CLR
# define YELLOW_CLR "\033[33m"
# define GREEN_CLR "\e[1;32m"
# define HEADLINE_CLR "\e[1;32m"
# define RESET_CLR "\033[0m"
#endif

class PhoneBook {
	public:
		PhoneBook();

		bool			add_contact(void);//set most these to private
		bool			search(void);
		unsigned int	getSize(void);
		void			setSize(unsigned int newSize);
		bool			add_field(std::string& field, const std::string& label);//put private
		unsigned int	toIndex(void);//put private

	private:
		Contact			_contacts[PHONEBOOK_SIZE];
		unsigned int	_index;
		unsigned int	_size;

		bool			_isValidNumber(const std::string& inputStr, unsigned int& result);
		bool			_inputFromStdin(std::string& inputStr);
};
