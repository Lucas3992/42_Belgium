#include "Zombie.hpp"

Zombie::Zombie() : nameTag("") {}

Zombie::~Zombie()
{
    std::cout << nameTag << " has been killed\n";
}

void Zombie::setName(std::string name)
{
    nameTag = name;
}

void Zombie::announce()
{
    std::cout << nameTag << ": BraiiiiiiinnnzzzZ...\n";
}
