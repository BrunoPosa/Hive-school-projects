#pragma once
#include <iostream>
#include <string>

class Contact {
	public:
		Contact();

		void		setFirstName(const std::string& s);
		void		setLastName(const std::string& s);
		void		setNickname(const std::string& s);
		void		setPhoneNumber(const std::string& s);
		void		setDarkSecret(const std::string& s);
		void		displayContact();
		std::string	getFirstName();
		std::string	getLastName();
		std::string	getNickname();
		std::string	getPhoneNumber();
		std::string	getDarkSecret();

	private:
		std::string FirstName;
		std::string LastName;
		std::string Nickname;
		std::string PhoneNum;
		std::string DarkSecret;
};
