#include "Poly.hpp"
#include "Wrong.hpp"

int main() {
    const Animal *meta = new Animal();
    const Animal *j = new Dog();
    const Animal *i = new Cat();

    std::cout << "-----------------------------------------------------------------------\n";

    std::cout << j->getType() << " says ";
    j->makeSound(); // dog sound

    std::cout << i->getType() << " says ";
    i->makeSound(); // will output the cat sound!

    std::cout << meta->getType() << " says ";
    meta->makeSound();

    std::cout << "-----------------------------------------------------------------------\n";

    delete j;
    delete i;
    delete meta;

    std::cout << "-----------------------------------------------------------------------\n";

    const WrongAnimal *wrongMeta = new WrongAnimal();
    const WrongAnimal *wc = new WrongCat();

    std::cout << "-----------------------------------------------------------------------\n";

    wrongMeta->makeSound();
    wc->makeSound(); //intentionaly bad sound

    std::cout << "-----------------------------------------------------------------------\n";

    delete wrongMeta;
    delete wc;

    std::cout << "-----------------------------------------------------------------------\n";

    return 0;
}
