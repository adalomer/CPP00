#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "phonebook.hpp"

// Constructor
PhoneBook::PhoneBook() : contactCount(0), oldestIndex(0)
{
}

// Destructor
PhoneBook::~PhoneBook()
{
}

// Helper: Get input from user (non-empty)
std::string PhoneBook::getInput(const std::string &prompt) const
{
	std::string input;

	while (true)
	{
		std::cout << prompt;
		if (!std::getline(std::cin, input))
		{
			std::cout << std::endl;
			return "";
		}
		if (!input.empty())
			return input;
		std::cout << "Field cannot be empty. Try again." << std::endl;
	}
}

// Helper: Truncate string to 10 chars
std::string PhoneBook::truncateStr(const std::string &str) const
{
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	return str;
}

// Add a new contact
void PhoneBook::addContact()
{
	Contact newContact;
	std::string input;

	std::cout << "=== ADD NEW CONTACT ===" << std::endl;

	input = getInput("First Name: ");
	if (input.empty()) return;
	newContact.setFirstName(input);

	input = getInput("Last Name: ");
	if (input.empty()) return;
	newContact.setLastName(input);

	input = getInput("Nickname: ");
	if (input.empty()) return;
	newContact.setNickname(input);

	input = getInput("Phone Number: ");
	if (input.empty()) return;
	newContact.setPhoneNumber(input);

	input = getInput("Darkest Secret: ");
	if (input.empty()) return;
	newContact.setDarkestSecret(input);

	// Add contact (replace oldest if full)
	contacts[oldestIndex] = newContact;
	oldestIndex = (oldestIndex + 1) % 8;
	if (contactCount < 8)
		contactCount++;

	std::cout << "Contact added successfully!" << std::endl;
}

// Display all contacts in a table
void PhoneBook::displayContacts() const
{
	std::cout << std::endl;
	std::cout << "|" << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First Name" << "|";
	std::cout << std::setw(10) << "Last Name" << "|";
	std::cout << std::setw(10) << "Nickname" << "|" << std::endl;
	std::cout << "|----------|----------|----------|----------|" << std::endl;

	for (int i = 0; i < contactCount; i++)
	{
		std::cout << "|" << std::setw(10) << i << "|";
		std::cout << std::setw(10) << truncateStr(contacts[i].getFirstName()) << "|";
		std::cout << std::setw(10) << truncateStr(contacts[i].getLastName()) << "|";
		std::cout << std::setw(10) << truncateStr(contacts[i].getNickname()) << "|" << std::endl;
	}
	std::cout << std::endl;
}

// Display single contact detail
void PhoneBook::displayContactDetail(int index) const
{
	std::cout << std::endl;
	std::cout << "First Name: " << contacts[index].getFirstName() << std::endl;
	std::cout << "Last Name: " << contacts[index].getLastName() << std::endl;
	std::cout << "Nickname: " << contacts[index].getNickname() << std::endl;
	std::cout << "Phone Number: " << contacts[index].getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret: " << contacts[index].getDarkestSecret() << std::endl;
	std::cout << std::endl;
}

// Search contacts
void PhoneBook::searchContact()
{
	if (contactCount == 0)
	{
		std::cout << "Phonebook is empty!" << std::endl;
		return;
	}

	displayContacts();

	std::string input;
	std::cout << "Enter index to view details: ";
	if (!std::getline(std::cin, input) || input.empty())
	{
		std::cout << "Invalid input." << std::endl;
		return;
	}

	// Check if input is a valid number
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!std::isdigit(input[i]))
		{
			std::cout << "Invalid index. Please enter a number." << std::endl;
			return;
		}
	}

	int index = std::atoi(input.c_str());
	if (index < 0 || index >= contactCount)
	{
		std::cout << "Index out of range." << std::endl;
		return;
	}

	displayContactDetail(index);
}

int main(void)
{
	PhoneBook phoneBook;
	std::string input;

	std::cout << "Welcome to PhoneBook!" << std::endl;
	std::cout << "Commands: ADD, SEARCH, EXIT" << std::endl;

	while (true)
	{
		std::cout << "> ";
		if (!std::getline(std::cin, input))
		{
			std::cout << std::endl << "EOF received. Goodbye!" << std::endl;
			break;
		}

		if (input == "ADD")
			phoneBook.addContact();
		else if (input == "SEARCH")
			phoneBook.searchContact();
		else if (input == "EXIT")
		{
			std::cout << "Goodbye!" << std::endl;
			break;
		}
		else if (!input.empty())
			std::cout << "Invalid command. Use ADD, SEARCH or EXIT." << std::endl;
	}
	return 0;
}