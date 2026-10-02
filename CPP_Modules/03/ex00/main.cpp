#include "ClapTrap.hpp"

int main() {
    ClapTrap mj("Marie-Jeanne");

	for (int i = 0; i < 5; i++)
	{
		mj.setAd(0);
		mj.attack("herself");
		mj.beRepaired(1);
		std::cout << "--------------------------------------------------------------------\n";
	}
	return 0;
}