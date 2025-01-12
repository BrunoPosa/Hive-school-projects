#include "Contact.class.hpp"

Contact::Contact() {}

void	Contact::setFirstName(const std::string& s) {
	FirstName = s;
}

void	Contact::setLastName(const std::string& s) {
	LastName = s;
}

void	Contact::setNickname(const std::string& s) {
	Nickname = s;
}

void	Contact::setPhoneNumber(const std::string& s) {
	PhoneNum = s;
}

void	Contact::setDarkSecret(const std::string& s) {
	DarkSecret = s;
}

void	Contact::displayContact() {
	std::cout << "First Name  : " << FirstName << std::endl;
	std::cout << "Last Name   : " << LastName << std::endl;
	std::cout << "Nickname    : " << Nickname << std::endl;
	std::cout << "Phone Number: " << PhoneNum << std::endl;
	std::cout << "Dark Secret : " << DarkSecret << std::endl;
}

std::string	Contact::getFirstName() {
	return (FirstName);
}

std::string	Contact::getLastName() {
	return (LastName);
}

std::string	Contact::getNickname() {
	return (Nickname);
}

std::string	Contact::getPhoneNumber() {
	return (PhoneNum);
}

std::string	Contact::getDarkSecret() {
	return (DarkSecret);
}
