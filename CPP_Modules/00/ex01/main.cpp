#include "PhoneBook.hpp"

int main(int ac, char **av)
{
    std::string command;

    (void)av;
    if (ac != 1)
    {
        std::cout << "Error: usage: ./phonebook\n";
        return 1;
    }
    else
    {
        PhoneBook pb;
        std::cout << "Welcome to the crappy awesome PhoneBook!\n";
        while (1)
        {
            std::cout << "Enter a command\n";
            if (!std::getline(std::cin, command))
                break ;
            if (command == "ADD")
                pb.addContact();
            else if (command == "SEARCH")
                pb.searchContact();
            else if (command == "EXIT")
                break ;
        }
    }
    return 0;
}
