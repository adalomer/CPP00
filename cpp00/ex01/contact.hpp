#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact
{
private:
	std::string	_firstName;
	std::string	_lastName;
	std::string	_nickname;
	std::string	_phone;
	std::string	_secret;

public:
	void	setInfo(std::string fn, std::string ln, std::string nn, std::string ph, std::string sc);
	std::string	getField(int i) const;
	bool	isEmpty() const;
};

#endif
