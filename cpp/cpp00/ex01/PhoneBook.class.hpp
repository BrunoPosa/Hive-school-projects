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

/* Between 1 and unsigned int or other system limit */
#ifndef PHONEBOOK_SIZE
# define PHONEBOOK_SIZE 2
#endif

#ifndef MAIN_INPUT_BUFFER_SIZE
# define MAIN_INPUT_BUFFER_SIZE 1024
#endif

#ifndef YELLOW_CLR
# define YELLOW_CLR "\033[33m"
# define RESET_CLR "\033[0m"
#endif

class PhoneBook {
	public:
		PhoneBook();

		bool			add_contact(void);
		bool			search();
		bool			add_field(std::string& field, const std::string& label);//put private
		unsigned int	toIndex(void);//put private

	private:
		Contact			_contacts[PHONEBOOK_SIZE];
		unsigned int	_index;

		unsigned int	_indexCheck(unsigned int i);
};
