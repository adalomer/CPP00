#include "contact.hpp"

void Contact::setInfo(std::string fn, std::string ln, std::string nn, std::string ph, std::string sc)
{
	_firstName = fn;
	_lastName = ln;
	_nickname = nn;
	_phone = ph;
	_secret = sc;
}

std::string Contact::getField(int i) const
{
	if (i == 0) return _firstName;
	if (i == 1) return _lastName;
	if (i == 2) return _nickname;
	if (i == 3) return _phone;
	return _secret;
}

bool Contact::isEmpty() const { return _firstName.empty(); }
