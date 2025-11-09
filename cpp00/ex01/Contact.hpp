#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>
# include <iostream>
# include <iomanip>

class Contact
{
private:
	std::string	firstName;
	std::string	lastName;
	std::string	nickname;
	std::string	phoneNumber;
	std::string	darkestSecret;
	
	std::string	truncate(std::string str);

public:
	Contact();
	~Contact();
		void	setContact(std::string fn, std::string ln, std::string nn,
				std::string pn, std::string ds);
	void	displayShort();
	void	displayFull();
	
	std::string	getFirstName() const;
	std::string	getLastName() const;
	std::string	getNickname() const;
	std::string	getPhoneNumber() const;
	std::string	getDarkestSecret() const;
};

#endif
