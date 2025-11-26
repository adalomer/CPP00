#include <iostream>
#include <string>

int main(void)
{

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

		}
		else if(input == "SEARCH")
		{

		}
		else if(input == "EXIT")
		{

		}
		else
			std::cout << "this is not true, try ready what i said";

	}
	return(0);
}