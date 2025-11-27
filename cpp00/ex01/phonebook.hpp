#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <iomanip>
#include "contact.hpp"

class PhoneBook
{
private:
	Contact	_contacts[8];
	int		_count;
	int		_oldest;

public:
	PhoneBook();
	void	add();
	void	search();
};

#endif