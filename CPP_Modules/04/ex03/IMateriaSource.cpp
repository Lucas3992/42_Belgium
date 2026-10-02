#include "IMateriaSource.hpp"

IMateriaSource::IMateriaSource() {}

IMateriaSource::IMateriaSource(const IMateriaSource& other) {
    (void)other;
}

IMateriaSource& IMateriaSource::operator=(const IMateriaSource& other) {
    (void)other;
    return *this;
}

IMateriaSource::~IMateriaSource() {}

MateriaSource::MateriaSource() {
    for (int i = 0; i < 4; i++)
        slots[i] = 0;
}

MateriaSource::MateriaSource(const MateriaSource& other) : IMateriaSource(other) {
    for (int i = 0; i < 4; i++) {
			delete slots[i];
			if (other.slots[i])
				slots[i] = other.slots[i]->clone();
			else
				slots[i] = 0;
	}
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
			delete slots[i];
			if (other.slots[i])
				slots[i] = other.slots[i]->clone();
			else
				slots[i] = 0;
		}
	}
    return *this;
}

MateriaSource::~MateriaSource() {
    for (int i = 0; i < 4; i++)
        delete slots[i];
}

void MateriaSource::learnMateria(AMateria* m) {
	if (!m)
		return ;
    for (int i = 0; i < 4; i++) {
        if (!slots[i]) {
			slots[i] = m->clone();
			delete m;
			return;
		}
    }
	delete m;//si slot est full sinon leaks
}

AMateria* MateriaSource::createMateria(std::string const& type) {
	for (int i = 0; i < 4; i++) {
		if (slots[i] && slots[i]->getType() == type)
			return slots[i]->clone();
	}
	std::cout << RED << "Wrong type\n" << RESET;
    return 0;
}