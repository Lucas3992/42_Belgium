#include "Zombie.hpp"

void randomChump(std::string name)
{
	Zombie newZ = Zombie(name);

	newZ.announce();
}
