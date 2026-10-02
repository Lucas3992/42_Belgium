#include "Poly.hpp"

/* lobjet existe que quand
sa classe de base est construite -> Animal;
tous ses membres sont construits -> Brain;
puis seulement lobjet dog ou cat
sinon lobjet serait incomplet */

int main() {
    Animal* animals[4];

    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
		animals[i]->makeSound();
    }
    std::cout << "-----------------------------------------------------------------------\n";

	for (int i = 0; i < 4; i++)
		delete animals[i];
    std::cout << "-----------------------------------------------------------------------\n";

	Dog d1;
	Dog d2 = d1;
    std::cout << "-----------------------------------------------------------------------\n";

	Cat c1;
	Cat c2(c1);
    std::cout << "-----------------------------------------------------------------------\n";

    return 0;
}
