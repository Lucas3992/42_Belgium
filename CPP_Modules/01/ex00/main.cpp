#include "Zombie.hpp"

int main()
{
	randomChump("Jean-Eude");
	Zombie* newZ = newZombie("Eude-jean");

	newZ->announce();
	delete newZ;
	return 0;
}
