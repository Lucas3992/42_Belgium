#include "PhoneBook.hpp"

int PhoneBook::isValidEntry(char c)
{
	if (c && c >= '1' && c <= '8')
		return 1;
	return 0;
}

int	PhoneBook::contactExists(int index)
{
	if (index < 1 || index > size)
		return 0;
	return 1;
}

void Contact::displayContact()
{
	std::cout << "First name: " << first_name << "\n";
	std::cout << "Last name: " << last_name << "\n";
	std::cout << "Nickname: " << nickname << "\n";
	std::cout << "Phone number: " << phone_number << "\n";
	std::cout << "Darkest secret: " << darkest_secret << "\n";
}

void PhoneBook::searchContact()
{
	std::string	entry;
	int			index;

	while (1)
	{
		displayPhoneBook();
		if (size < 1)
		{
			std::cout << "The PhoneBook is empty. Please ADD a contact first\n";
			break ;
		}
		std::cout << "Select the contact's index you want to display\n";
		if (!std::getline(std::cin, entry))
			return ;
		if (entry.length() == 1 && isValidEntry(entry[0]))
		{
			index = entry[0] -'0';
			if (contactExists(index))
			{
				contacts[index - 1].displayContact();
				break;
			}
			else
				std::cout << "No contact exists at that index\n";
		}
		else
			std::cout << "Please enter a digit between 1 and " << size << "\n";
	}
}
