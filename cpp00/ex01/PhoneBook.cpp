#include <cstdlib>
#include "PhoneBook.hpp"
#include <cctype>
#include <cstring>
// Constructor
PhoneBook::PhoneBook() : _count(0), _oldest(0) {}

// Helper: Get input from user (non-empty)
static std::string getInput(std::string prompt)
{
	std::string s;
	while (s.empty())
	{
		std::cout << prompt;
		std::getline(std::cin, s);
		for(int i = 0;i < (int)s.length();i++)
		{
			if(!(std::isprint(s[i])))
			{
				std::cout << "NON printable" <<std::endl;
				return "";
			}
		}
	}
	return s;
}

// Helper: Truncate string to 10 chars
static std::string truncate(std::string s)
{
	return (s.length() > 10) ? s.substr(0, 9) + "." : s;
}

// Add a new contact
void PhoneBook::add()
{
	std::string f[5];
	std::string prompts[] = {"First Name: ", "Last Name: ", "Nickname: ", "Phone: ", "Secret: "};

	for (int i = 0; i < 5; i++)
	{
		f[i] = getInput(prompts[i]);
		if (f[i].empty()) return;
	}
	_contacts[_oldest].setInfo(f[0], f[1], f[2], f[3], f[4]);
	_oldest = (_oldest + 1) % 8;
	if (_count < 8) _count++;
	std::cout << "Contact added!" << std::endl;
}

// Search contacts
void PhoneBook::search()
{
	if (_count == 0) { std::cout << "Empty!, u need enter number" << std::endl; return; }

	std::cout << "|" << std::setw(10) << "Index" << "|" << std::setw(10) << "First"
		<< "|" << std::setw(10) << "Last" << "|" << std::setw(10) << "Nick" << "|" << std::endl;

	for (int i = 0; i < _count; i++)
		std::cout << "|" << std::setw(10) << i << "|" << std::setw(10) << truncate(_contacts[i].getField(0))
		<< "|" << std::setw(10) << truncate(_contacts[i].getField(1))
		<< "|" << std::setw(10) << truncate(_contacts[i].getField(2)) << "|" << std::endl;

	std::string in;
	std::cout << "Index: ";
	if (!std::getline(std::cin, in) || in.empty()) return;

	// Check if input is a valid number
	for (size_t i = 0; i < in.length(); i++)
	{
		if (in[i] < '0' || in[i] > '9')
		{
			std::cout << "Invalid index, RTFM!" << std::endl;
			return;
		}
	}

	int idx = std::atoi(in.c_str());
	if (idx < 0 || idx >= _count) { std::cout << "Invalid index, RTFM!" << std::endl; return; }

	std::string labels[] = {"First Name", "Last Name", "Nickname", "Phone", "Secret"};
	for (int i = 0; i < 5; i++)
		std::cout << labels[i] << ": " << _contacts[idx].getField(i) << std::endl;
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
			std::cout << "Commands: ADD, SEARCH, EXIT, do u blind?"<< std::endl;
	}
	return 0;
}