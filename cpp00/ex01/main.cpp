#include "Phonebook.hpp"
#include <iostream>
#include <string>

int	main(void)
{
	PhoneBook	phoneBook;
	std::string	command;
	
	std::cout << "=== PHONEBOOK ===" << std::endl;
	std::cout << "Commands: ADD, SEARCH, EXIT" << std::endl;
	
	while (true)
	{
		std::cout << "\n> ";
		std::getline(std::cin, command);
		
		if (std::cin.eof())
		{
			std::cout << "\nEOF detected. Exiting..." << std::endl;
			break ;
		}
		
		if (command == "ADD")
			phoneBook.addContact();
		else if (command == "SEARCH")
			phoneBook.searchContact();
		else if (command == "EXIT")
		{
			std::cout << "Goodbye!" << std::endl;
			break ;
		}
		else if (!command.empty())
			std::cout << "Invalid command! Use: ADD, SEARCH, EXIT" << std::endl;
	}
	
	return (0);
}
