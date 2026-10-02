#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {}

ClapTrap::ClapTrap(const std::string newName) :
name(newName), hp(10), ep(10), ad(0), maxHp(10) {
	if (hp < 0 || ep < 0 || ad < 0)
	{
		std::cout << "HP, EP & AD must be positive\n";
		return ;
	}
    std::cout << "ClapTrap created\n";
}

ClapTrap::ClapTrap(const ClapTrap& other) {
    this->operator=(other);
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
    name = other.name;
    hp = other.hp;
    ep = other.ep;
    ad = other.ad;
	maxHp = other.maxHp;
    return *this;
}

void ClapTrap::setAd(unsigned int newAd){
	ad = newAd;
	if ((int)newAd < 0)
	{
		std::cout << "Attack damage must be positive\n";
		return ;
	}
}

ClapTrap::~ClapTrap() {std::cout << "Destructor called\n";}

void ClapTrap::attack(const std::string& target) {
    if (ep < 1 || hp < 1 || ad < 0)
	{
		std::cout << "Can't do any actions\n";
        return ;
	}
    std::cout << "EP: " << ep << " | HP: " << hp << std::endl;
    std::cout << "ClapTrap " << name << " attacks " << target
    << ", causing " << ad << " points of damage!\n";
    ep--;
    std::cout << "EP downed to " << ep << std::endl;
	takeDamage(ad);
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (hp < 1)
		return ;
	if ((int)amount < 0)
	{
		std::cout << "The amount you want to damage must be positive.\n";
		return ;
	}
	else if ((unsigned int)hp < amount)
	{
		hp = 0;
		std::cout << "But the damage is too damn high! HP set to 0\n";
		return ;
	}
	else
	{
		hp -= amount;
		std::cout << "HP has been decreased by " << amount << std::endl;
		std::cout << "New HP: " << hp << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (ep < 1 || hp < 1)
        return ;
	else if ((int)amount < 0)
	{
		std::cout << "The amount you want to heal must be positive. Can't heal\n";
		return ;
	}
    hp += amount;
	if (hp < maxHp)
		std::cout << "HP has been increased by " << amount << std::endl;
	else
	{	
		hp = maxHp;
		std::cout << name << " tries to repair but her HP is too damn high!\n";
	}
	ep--;
    std::cout << "EP downed to " << ep << std::endl;
    std::cout << "EP: " << ep << " | HP: " << hp << std::endl;
}

