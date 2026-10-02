#include "ScavTrap.hpp"

ScavTrap::ScavTrap() {}

ScavTrap::ScavTrap(const std::string& newName) : ClapTrap(newName) {
    std::cout << RED << "ScavTrap created\n" << RESET;
    hp = 100;
    ep = 50;
    ad = 20;
    maxHp = 100;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
    std::cout << RED << "ScavTrap copy constructor called\n" << RESET;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
    ClapTrap::operator=(other);
    std::cout << RED << "ScavTrap copy assignment operator called\n" << RESET;
    return *this;
}

ScavTrap::~ScavTrap() {std::cout << RED << "ScavTrap destroyed\n" << RESET;}

void ScavTrap::guardGate() {
    std::cout << RED << "Gate Keeper activated, YOU SHALL NOT PAAAASSSSS\n" << RESET;
}

void ScavTrap::attack(const std::string& target) {
    if (ep < 1 || hp < 1 || ad < 0)
	{
		std::cout << "Can't do any actions\n";
        return ;
	}
    std::cout << RED << "EP: " << ep << " | HP: " << hp << std::endl;
    std::cout << "ScavTrap " << name << " attacks " << target
    << ", causing " << ad << " points of damage!\n";
    ep--;
    std::cout << "EP downed to " << ep << RESET << std::endl;
	takeDamage(ad);
}
