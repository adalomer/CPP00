#include "Contact.hpp"

Contact::Contact()
{
}

Contact::~Contact()
{
}

void	Contact::setContact(std::string fn, std::string ln, std::string nn,
						std::string pn, std::string ds)
{
	this->firstName = fn;
	this->lastName = ln;
	this->nickname = nn;
	this->phoneNumber = pn;
	this->darkestSecret = ds;
}

std::string	Contact::truncate(std::string str)
{
	if (str.length() > 10)
		return (str.substr(0, 9) + ".");
	return (str);
}

void	Contact::displayShort()
{
	std::cout << std::setw(10) << truncate(this->firstName) << "|";
	std::cout << std::setw(10) << truncate(this->lastName) << "|";
	std::cout << std::setw(10) << truncate(this->nickname) << std::endl;
}

void	Contact::displayFull()
{
	std::cout << "First Name: " << this->firstName << std::endl;
	std::cout << "Last Name: " << this->lastName << std::endl;
	std::cout << "Nickname: " << this->nickname << std::endl;
	std::cout << "Phone Number: " << this->phoneNumber << std::endl;
	std::cout << "Darkest Secret: " << this->darkestSecret << std::endl;
}

std::string	Contact::getFirstName() const
{
	return (this->firstName);
}

std::string	Contact::getLastName() const
{
	return (this->lastName);
}

std::string	Contact::getNickname() const
{
	return (this->nickname);
}

std::string	Contact::getPhoneNumber() const
{
	return (this->phoneNumber);
}

std::string	Contact::getDarkestSecret() const
{
	return (this->darkestSecret);
}
