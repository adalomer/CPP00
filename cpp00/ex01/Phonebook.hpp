#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include "Contact.hpp"
# include <iostream>
# include <iomanip>
# include <string>

class PhoneBook
{
private:
	Contact	contacts[8];
	int		contactCount;
	int		oldestIndex;

public:
	PhoneBook();
	~PhoneBook();
	
	void	addContact();
	void	searchContact();
	void	displayContacts();
};

#endif
