#include "ICharacter.hpp"
#include "AMateria.hpp"
#include "IMateriaSource.hpp"

int main() {
    IMateriaSource *src = new MateriaSource();
    AMateria *tmp;
    ICharacter *me = new Character("me");
    ICharacter *bob = new Character("bob");

    for (int i = 0; i < 4; i++) {//on remplit trop de materia
        src->learnMateria(new Ice());
        src->learnMateria(new Cure());
    }

    me->unequip(0);//test denequip un slot vide

    tmp = src->createMateria("ice");
    me->equip(tmp);

    for (int i = 0; i < 5; i++) { //essaie dequiper 6 materia dans 4 slots
        tmp = src->createMateria("cure");
        me->equip(tmp);
    }
    std::cout << "-----------------------------------------------------------------------\n";
    
    me->use(0, *bob);
    me->use(1, *bob);
    me->use(9, *me);//mauvais index
    std::cout << "-----------------------------------------------------------------------\n";

    me->unequip(0);
    me->use(0, *me);//essaie dutiliser une materia laissee au sol
    std::cout << "-----------------------------------------------------------------------\n";


    tmp = src->createMateria("curse");//mauvais type
    me->equip(tmp);
    me->use(0, *bob);
    std::cout << "-----------------------------------------------------------------------\n";

    tmp = src->createMateria("ice");
    me->equip(tmp);
    me->equip(tmp);//test dequiper deux fois la meme materia

    delete bob; //check delete pour le floor
    delete me;

    ICharacter *test = new Character("test");
    tmp = src->createMateria("cure");
    test->equip(tmp);
    test->use(0, *test);
    test->unequip(0);
    std::cout << "-----------------------------------------------------------------------\n";

    delete test;
    delete src;

    return 0;
}
