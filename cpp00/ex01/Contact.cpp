#include "Contact.hpp"
#include "Colors.hpp"

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
	std::cout << BOLD_CYAN << "\n╔═══════════════ CONTACT INFO ═══════════════╗" << RESET << std::endl;
	std::cout << BOLD_GREEN << "👤 First Name:     " << RESET << this->firstName << std::endl;
	std::cout << BOLD_YELLOW << "👥 Last Name:      " << RESET << this->lastName << std::endl;
	std::cout << BOLD_BLUE << "🎭 Nickname:       " << RESET << this->nickname << std::endl;
	std::cout << BOLD_MAGENTA << "📞 Phone Number:   " << RESET << this->phoneNumber << std::endl;
	std::cout << BOLD_RED << "🤫 Darkest Secret: " << RESET << this->darkestSecret << std::endl;
	std::cout << BOLD_CYAN << "╚════════════════════════════════════════════╝" << RESET << std::endl;
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
