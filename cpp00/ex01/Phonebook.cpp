#include "Phonebook.hpp"

PhoneBook::PhoneBook() : contactCount(0), oldestIndex(0) {}

PhoneBook::~PhoneBook() {}

static std::string	getInput(const std::string &prompt)
{
	std::string	input;
	
	std::cout << prompt;
	std::getline(std::cin, input);
	return (input);
}

void	PhoneBook::addContact()
{
	std::string	fields[5];
	std::string	prompts[5] = {"First Name: ", "Last Name: ", "Nickname: ", 
								"Phone Number: ", "Darkest Secret: "};
	int			i;
	
	i = 0;
	while (i < 5)
	{
		fields[i] = getInput(prompts[i]);
		if (fields[i].empty())
		{
			std::cout << "Error: Empty field!" << std::endl;
			return ;
		}
		i++;
	}
	
	this->contacts[this->oldestIndex].setContact(fields[0], fields[1], 
												fields[2], fields[3], fields[4]);
	this->oldestIndex = (this->oldestIndex + 1) % 8;
	if (this->contactCount < 8)
		this->contactCount++;
	std::cout << "Contact added successfully!" << std::endl;
}

void	PhoneBook::searchContact()
{
	std::string	input;
	int			index;
	
	if (this->contactCount == 0)
		return ((void)(std::cout << "PhoneBook is empty!" << std::endl));
	
	displayContacts();
	input = getInput("\nEnter index: ");
	
	if (input.length() != 1 || !isdigit(input[0]))
		return ((void)(std::cout << "Invalid index!" << std::endl));
	
	index = input[0] - '0';
	if (index < 0 || index >= this->contactCount)
		return ((void)(std::cout << "Invalid index!" << std::endl));
	
	this->contacts[index].displayFull();
}

void	PhoneBook::displayContacts()
{
	int	i;
	
	std::cout << std::setw(10) << "Index" << "|"
			<< std::setw(10) << "First Name" << "|"
			<< std::setw(10) << "Last Name" << "|"
			<< std::setw(10) << "Nickname" << std::endl;
	
	i = -1;
	while (++i < this->contactCount)
	{
		std::cout << std::setw(10) << i << "|";
		this->contacts[i].displayShort();
	}
}
