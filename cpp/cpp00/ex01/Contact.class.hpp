/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:25:04 by bposa             #+#    #+#             */
/*   Updated: 2025/01/15 00:38:05 by bposa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

#ifndef CONTACT_COLUMN_WIDTH
# define CONTACT_COLUMN_WIDTH 10
#endif

#ifndef CONTACT_STR_TRIM_CHAR
# define CONTACT_STR_TRIM_CHAR '.'
#endif

class Contact {
	public:
		Contact() = default;
		Contact(const std::string firstName,
				const std::string lastName,
				const std::string nickName,
				const std::string phoneNum,
				const std::string darkSecret);

		std::string&	getFirstName();
		std::string&	getLastName();
		std::string&	getNickname();
		std::string&	getPhoneNumber();
		std::string&	getDarkSecret();

		void		showContactPage();
		void		showContactRow();

	private:
		std::string	_trim(std::string& str);
		std::string _firstName;
		std::string _lastName;
		std::string _nickname;
		std::string _phoneNum;
		std::string _darkSecret;
};
