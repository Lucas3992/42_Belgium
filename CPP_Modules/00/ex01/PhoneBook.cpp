#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	size = 0;
	index = 0;
}

static std::string formatName(std::string str)
{
	if (str.length() > 10)
		return str.substr(0, 9) + ".";
	while (str.length() < 10)
		str.insert(0, " ");
	return str;
}

void PhoneBook::displayContactInColumn(int index)
{
	std::string fn = contacts[index].getFirstName();
	std::string ln = contacts[index].getLastName();
	std::string nn = contacts[index].getNickname();

	std::cout << "|" << "         " << index +1 << "|";
	std::cout << formatName(fn) << "|";
	std::cout << formatName(ln) << "|";
	std::cout << formatName(nn) << "|\n";
}

void PhoneBook::displayPhoneBook()
{
	std::cout << "|" << "     INDEX" << "|" << "FIRST NAME" << "|" << " LAST NAME" << "|" << "  NICKNAME" << "|\n";
	for (int i = 0; i < size; i++)
		displayContactInColumn(i);
}
