#include "AMateria.hpp"

AMateria::AMateria() : type("unknown") {}

AMateria::AMateria(std::string const& t) : type(t) {}

AMateria::AMateria(const AMateria& other) : type(other.type) {}

AMateria& AMateria::operator=(const AMateria& other) {
    (void)other;
    return *this;
}

AMateria::~AMateria() {}

std::string const& AMateria::getType() const {
    return type;
}

Ice::Ice() : AMateria("ice") {}

Ice::Ice(const Ice& other) : AMateria(other) {}

Ice& Ice::operator=(const Ice& other) {
    if (this != &other)
        AMateria::operator=(other);
    return *this;
}

Ice::~Ice() {}

Ice* Ice::clone() const {
    return new Ice(*this);
}

void Ice::use(ICharacter& target) {
    std::cout << BLUE << "* shoots an ice bolt at " << target.getName() << " *\n" << RESET;
}

Cure::Cure() : AMateria("cure") {}

Cure::Cure(const Cure& other) : AMateria(other) {}

Cure& Cure::operator=(const Cure& other) {
    if (this != &other)
        AMateria::operator=(other);
    return *this;
}

Cure::~Cure() {}

Cure* Cure::clone() const {
    return new Cure(*this);
}

void Cure::use(ICharacter& target) {
    std::cout << GREEN << "* heals " << target.getName() << "'s wounds*\n" << RESET;
}