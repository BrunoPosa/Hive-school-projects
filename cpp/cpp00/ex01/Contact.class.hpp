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

#ifndef CONTACT_CLASS_HPP
# define CONTACT_CLASS_HPP

#include <iostream>

# define CONTACT_COLUMN_WIDTH 10
# define CONTACT_STR_TRIM_CHAR '.'

class Contact {
	public:
		Contact() = default;
		Contact(const std::string firstName,
				const std::string lastName,
				const std::string nickName,
				const std::string phoneNum,
				const std::string darkSecret);

		std::string&	getFirstName(void);
		std::string&	getLastName(void);
		std::string&	getNickname(void);
		std::string&	getPhoneNumber(void);
		std::string&	getDarkSecret(void);

		void		showContactPage(void);
		void		showContactRow(void);

	private:
		std::string	_trim(std::string& str);
		std::string _firstName;
		std::string _lastName;
		std::string _nickname;
		std::string _phoneNum;
		std::string _darkSecret;
};

#endif