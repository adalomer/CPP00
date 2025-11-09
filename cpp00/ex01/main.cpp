#include "Phonebook.hpp"
#include "Colors.hpp"
#include <iostream>
#include <string>

int	main(void)
{
	PhoneBook	phoneBook;
	std::string	command;
	
	std::cout << BOLD_CYAN << "\n╔═══════════════════════════════════╗\n";
	std::cout << "║   📞  AWESOME PHONEBOOK 3000  📞  ║\n";
	std::cout << "╚═══════════════════════════════════╝" << RESET << std::endl;
	std::cout << BOLD_YELLOW << "\n💡 Commands: " << BOLD_GREEN << "ADD" 
			  << YELLOW << " | " << BOLD_BLUE << "SEARCH" 
			  << YELLOW << " | " << BOLD_RED << "EXIT" << RESET << std::endl;
	
	while (true)
	{
		std::cout << BOLD_CYAN << "\n⚡ > " << RESET;
		std::getline(std::cin, command);
		
		if (std::cin.eof())
		{
			std::cout << BOLD_RED << "\n🚨 EOF detected. Hasta la vista, baby! 👋" << RESET << std::endl;
			break ;
		}
		
		if (command == "ADD")
			phoneBook.addContact();
		else if (command == "SEARCH")
			phoneBook.searchContact();
		else if (command == "EXIT")
		{
			std::cout << BOLD_GREEN << "👋 Goodbye! Don't forget to call your mom! 💚" << RESET << std::endl;
			break ;
		}
		else if (!command.empty())
			std::cout << BOLD_RED << "❌ Bruh... That's not a command! 🤦 Try: " 
					  << BOLD_GREEN << "ADD" << WHITE << ", " 
					  << BOLD_BLUE << "SEARCH" << WHITE << ", or " 
					  << BOLD_RED << "EXIT" << RESET << std::endl;
	}
	
	return (0);
}
