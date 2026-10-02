#ifndef SCAVTRAP_H
# define SCAVTRAP_H

#include "ClapTrap.hpp"

class ScavTrap: public ClapTrap {
    public:
		ScavTrap();
        ScavTrap(const std::string& name);
        ScavTrap(const ScavTrap& other);
        ScavTrap& operator=(const ScavTrap& other);
        ~ScavTrap();

        void    attack(const std::string& target);
        void    guardGate();
};

# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define BLUE    "\033[34m"
# define RESET   "\033[0m"

#endif