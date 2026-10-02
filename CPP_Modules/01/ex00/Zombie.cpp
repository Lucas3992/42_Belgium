#include "Zombie.hpp"

Zombie::Zombie(std::string name) : nameTag(name) {}

Zombie::~Zombie()
{
    std::cout << nameTag << " has been killed\n";
}

void Zombie::announce()
{
    std::cout << nameTag << ": BraiiiiiiinnnzzzZ...\n";
}
