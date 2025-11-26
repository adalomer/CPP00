#include <iostream>
#include <string>
#include "phonebook.hpp"

int main(void)
{
	PhoneBook PhoneBook;
	std::cout << "Pls enter ADD, SEARCH, EXIT";
	while(true)
	{
		std::string input;
		std::cout << std::endl;
		std::getline(std::cin,input);

		if(std::cin.eof())
		{
			std::cout << "i get signal to close this app, bye baby"<< std::endl;
			break ;
		}
		if(input == "ADD")
		{
			PhoneBook.addContact();
		}
		else if(input == "SEARCH")
		{
			PhoneBook.searchContact();
		}
		else if(input == "EXIT")
		{
			std::cout <<"i get exit input , pls rate 5 thank you"<<std::endl;
			break ;
		}
		else
			std::cout << "this is not true, try ready what i said";

	}
	return(0);
}

void PhoneBook::addContact()
{

}