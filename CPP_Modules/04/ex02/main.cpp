#include "Poly.hpp"

/* lobjet existe que quand
sa classe de base est construite -> Animal;
tous ses membres sont construits -> Brain;
puis seulement lobjet dog ou cat
sinon lobjet serait incomplet */

int main() {
    AAnimal* animals[4];

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

    //AAnimal aa; --> impossible pcq on peut pas creer dobjet abstrait
    //aa.makeSound();

    return 0;
}
