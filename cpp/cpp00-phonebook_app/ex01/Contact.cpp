#include "Contact.class.hpp"
#include <iomanip>

Contact::Contact(const std::string firstName,
				const std::string lastName,
				const std::string nickName,
				const std::string phoneNum,
				const std::string darkSecret)
			: _firstName(firstName), _lastName(lastName), _nickname(nickName), 
              _phoneNum(phoneNum), _darkSecret(darkSecret) {}

void	Contact::showContactPage()
{
	std::cout << "First Name  : " << _firstName << std::endl
			<< "Last Name   : " << _lastName << std::endl
			<< "Nickname    : " << _nickname << std::endl
			<< "Phone Number: " << _phoneNum << std::endl
			<< "Dark Secret : " << _darkSecret << std::endl;
}

void	Contact::showContactRow()
{
	std::cout << std::right
			<< std::setw(CONTACT_COLUMN_WIDTH) << _trim(_firstName) << "|"
			<< std::setw(CONTACT_COLUMN_WIDTH) << _trim(_lastName) << "|"
			<< std::setw(CONTACT_COLUMN_WIDTH) << _trim(_nickname) << "|" << std::endl;
}

std::string	Contact::_trim(std::string& str)
{
	if (str.length() > CONTACT_COLUMN_WIDTH)
		return (str.substr(0, CONTACT_COLUMN_WIDTH - 1) + CONTACT_STR_TRIM_CHAR);
	else
		return (str);
}
