#include "ScavTrap.hpp"

int main() {
    ScavTrap ps("Patrick Sebastien");

	for (int i = 0; i < 5; i++)
	{
		ps.guardGate();
		ps.attack("himself");
		ps.beRepaired(1);
		std::cout << "--------------------------------------------------------------------\n";
	}
	return 0;
}