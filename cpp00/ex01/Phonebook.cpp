#include "Phonebook.hpp"
#include "Colors.hpp"

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
			std::cout << BOLD_RED << "🤨 Empty field? Really? That's a no from me, dawg! " << RESET << std::endl;
			return ;
		}
		i++;
	}
	
	this->contacts[this->oldestIndex].setContact(fields[0], fields[1], 
												fields[2], fields[3], fields[4]);
	this->oldestIndex = (this->oldestIndex + 1) % 8;
	if (this->contactCount < 8)
		this->contactCount++;
	std::cout << BOLD_GREEN << "✨ Contact added! You're on fire! 🔥" << RESET << std::endl;
}

void	PhoneBook::searchContact()
{
	std::string	input;
	int			index;
	
	if (this->contactCount == 0)
		return ((void)(std::cout << BOLD_YELLOW << "🦗 *crickets* Your phonebook is emptier than my wallet! 💸" << RESET << std::endl));
	
	displayContacts();
	input = getInput(BOLD_CYAN "\n🔍 Enter index: " RESET);
	
	if (input.length() != 1 || !isdigit(input[0]))
		return ((void)(std::cout << BOLD_RED << "😂 That's not even a number! Did you skip math class? 🤪" << RESET << std::endl));
	
	index = input[0] - '0';
	if (index < 0 || index >= this->contactCount)
		return ((void)(std::cout << BOLD_RED << "🚫 Index out of bounds! Did you even look at the list? 👀" << RESET << std::endl));
	
	this->contacts[index].displayFull();
}

void	PhoneBook::displayContacts()
{
	int	i;
	
	std::cout << BOLD_MAGENTA << "\n╔════════════════════════════════════════════════╗" << RESET << std::endl;
	std::cout << BOLD_CYAN << std::setw(10) << "Index" << RESET << "|"
			<< BOLD_GREEN << std::setw(10) << "First Name" << RESET << "|"
			<< BOLD_YELLOW << std::setw(10) << "Last Name" << RESET << "|"
			<< BOLD_BLUE << std::setw(10) << "Nickname" << RESET << std::endl;
	std::cout << BOLD_MAGENTA << "╠════════════════════════════════════════════════╣" << RESET << std::endl;
	
	i = -1;
	while (++i < this->contactCount)
	{
		std::cout << BOLD_WHITE << std::setw(10) << i << RESET << "|";
		this->contacts[i].displayShort();
	}
	std::cout << BOLD_MAGENTA << "╚════════════════════════════════════════════════╝" << RESET << std::endl;
}
