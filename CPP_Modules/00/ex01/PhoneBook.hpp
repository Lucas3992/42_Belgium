#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <cctype>
#include <iostream>

class Contact {
	private:
		std::string	phone_number;
		std::string	first_name;
		std::string	last_name;
		std::string	nickname;
		std::string	darkest_secret;

	public:
		void		setPhoneNumber(std::string entry);
		void		setFirstName(std::string entry);
		void		setLastName(std::string entry);
		void		setNickname(std::string entry);
		void		setSecret(std::string entry);
		std::string	getFirstName();
		std::string	getLastName();
		std::string	getNickname();
		void		displayContact();
};

class PhoneBook {
	private:
		Contact	contacts[8];
		int		size;
		int		index;
		int 	contactExists(int index);
		int		isValidEntry(char c);

	public:
		PhoneBook();
		void	addContact();
		void	searchContact();
		void	displayPhoneBook();
		void	displayContactInColumn(int index);
};

#endif