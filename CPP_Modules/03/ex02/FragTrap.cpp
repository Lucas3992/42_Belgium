#include "FragTrap.hpp"

FragTrap::FragTrap() {}

FragTrap::FragTrap(const std::string& newName) : ClapTrap(newName) {
    std::cout << GREEN << "FragTrap created\n" << RESET;
    hp = 100;
    ep = 100;
    ad = 30;
    maxHp = 100;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
    std::cout << GREEN << "FragTrap copy constructor called\n" << RESET;
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
    ClapTrap::operator=(other);
    std::cout << GREEN << "FragTrap copy assignment operator called\n" << RESET;
    return *this;
}

FragTrap::~FragTrap() {std::cout << GREEN << "FragTrap destroyed\n" << RESET;}

void FragTrap::highFivesGuys() {
    std::cout << GREEN << "High Fives: *Emile takes a chewing gum*\n" << RESET;
}

void FragTrap::attack(const std::string& target) {
    if (ep < 1 || hp < 1 || ad < 0)
	{
		std::cout << "Can't do any actions\n";
        return ;
	}
    std::cout << GREEN << "EP: " << ep << " | HP: " << hp << std::endl;
    std::cout << "FragTrap " << name << " attacks " << target
    << ", causing " << ad << " points of damage!\n";
    ep--;
    std::cout << "EP downed to " << ep << RESET << std::endl;
	takeDamage(ad);
}
