#include "Zombie.hpp"

int main()
{
	int n = 5;
	Zombie* newHorde = zombieHorde(n, "Marie-Christine");

	for (int i = 0; i < n; i++)
		newHorde[i].announce();
	delete[] newHorde;
	return 0;
}
