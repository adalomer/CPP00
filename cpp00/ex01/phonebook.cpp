#include <cstdlib>
#include "phonebook.hpp"

// Constructor
PhoneBook::PhoneBook() : _count(0), _oldest(0) {}

// Helper: Get input from user (non-empty)
static std::string getInput(std::string prompt)
{
	std::string s;
	while (s.empty())
	{
		std::cout << prompt;
		if (!std::getline(std::cin, s))
			return "";
	}
	return s;
}

int main()
{
	PhoneBook pb;
	std::string cmd;

	std::cout << "Commands: ADD, SEARCH, EXIT" << std::endl;
	while (std::cout << "> " && std::getline(std::cin, cmd))
	{
		if (cmd == "ADD") pb.add();
		else if (cmd == "SEARCH") pb.search();
		else if (cmd == "EXIT") break;
		else
			std::cout << "Commands: ADD, SEARCH, EXIT"<< std::endl;
	}
	return 0;
}