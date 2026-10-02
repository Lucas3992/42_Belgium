#include "FragTrap.hpp"

int main() {
    FragTrap e("Emile");

	for (int i = 0; i < 5; i++)
	{
		e.highFivesGuys();
		e.attack("himself");
		e.beRepaired(1);
		std::cout << "--------------------------------------------------------------------\n";
	}
	return 0;
}