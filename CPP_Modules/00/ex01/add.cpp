#include "PhoneBook.hpp"

static int is_valid_number(std::string entry)
{
	int	len = entry.length();

	if (len != 10)
		return 0;
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(entry[i]))
			return 0;
	}
	return 1;
}

static int is_valid_name(std::string entry)
{
    int len = entry.length();

    if (len == 0)
        return 0;
    for (int i  = 0; i < len; i++)
    {
        if (!isalpha(entry[i]))
            return 0;
    }
    return 1;
}

static int is_valid_secret(std::string entry)
{
    int len = entry.length();

    if (len == 0)
        return 0;
    return 1;
}

void PhoneBook::addContact()
{
    std::string entry;
    int i = index;

    while (1)
    {
        std::cout << "Enter the first name\n";
        if (!std::getline(std::cin, entry))
            return ;
        if (is_valid_name(entry))
            break;
        std::cout << "Please enter a valid first name\n";
    }
    contacts[i].setFirstName(entry);

    while (1)
    {
        std::cout << "Enter the last name\n";
        if (!std::getline(std::cin, entry))
            return ;
        if (is_valid_name(entry))
            break;
        std::cout << "Please enter a valid last name\n";
    }
    contacts[i].setLastName(entry);

    while (1)
    {
        std::cout << "Enter the nickname\n";
        if (!std::getline(std::cin, entry))
            return ;
        if (is_valid_name(entry))
            break;
        std::cout << "Please enter a valid nickname\n";
    }
    contacts[i].setNickname(entry);

    while (1)
    {
        std::cout << "Enter a phone number\n";
        if (!std::getline(std::cin, entry))
            return ;
        if (is_valid_number(entry))
            break;
        std::cout << "Please enter a valid phone number\n";
    }
    contacts[i].setPhoneNumber(entry);

    while (1)
    {
        std::cout << "What's your darkest secret?\n";
        if (!std::getline(std::cin, entry))
            return ;
        if (is_valid_secret(entry))
            break;
        std::cout << "Come on, everybody has one\n";
    }
    contacts[i].setSecret(entry);

    if (size < 8)
        size++;
    index = (i +1) %8;
    std::cout << "The new contact has been correctly added to the PhoneBook\n";
}
