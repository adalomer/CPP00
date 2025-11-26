#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include "contact.hpp"

class PhoneBook
{
private:
	Contact	contacts[8];
	int		contactCount;
	int		oldestIndex;

	std::string	truncateStr(const std::string &str) const;
	std::string	getInput(const std::string &prompt) const;

public:
	PhoneBook();
	~PhoneBook();
	
	void	addContact();
	void	searchContact();
	void	displayContacts() const;
	void	displayContactDetail(int index) const;
};

#endif