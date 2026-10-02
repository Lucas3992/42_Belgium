#ifndef FRAGTRAP_H
# define FRAGTRAP_H

# include "ScavTrap.hpp"

class FragTrap : public ClapTrap {
    public:
		FragTrap();
        FragTrap(const std::string &name);
        FragTrap(const FragTrap &other);
        FragTrap &operator=(const FragTrap &other);
        ~FragTrap();

        void attack(const std::string &target);
        void highFivesGuys();
};

# define GREEN   "\033[32m"
# define RESET   "\033[0m"

#endif