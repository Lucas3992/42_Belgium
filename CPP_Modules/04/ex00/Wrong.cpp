#include "Wrong.hpp"

WrongAnimal::WrongAnimal() {std::cout << RED << "WrongAnimal constructor called\n" << RESET;}

WrongAnimal::WrongAnimal(const WrongAnimal& other) {
	operator=(other);
	std::cout << RED << "WrongAnimal copy constructor called\n" << RESET;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other) {
	type = other.type;
	std::cout << RED << "WrongAnimal copy assignment operator called\n" << RESET;
	return *this;
}

WrongAnimal::~WrongAnimal() {std::cout << RED << "WrongAnimal destructor called\n" << RESET;}

std::string WrongAnimal::getType() const {
	return type;
}

void WrongAnimal::makeSound() const {
    std::cout << RED << "*WrongAnimal sound*\n" << RESET;
}

WrongCat::WrongCat() {std::cout << RED << "WrongCat constructor called\n" << RESET;}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal (other) {
	operator=(other);
	std::cout << RED << "WrongCat copy constructor called\n" << RESET;
}

WrongCat& WrongCat::operator=(const WrongCat& other) {
	(void)other;
	std::cout << RED << "WrongCat copy assignment operator called\n" << RESET;
	return *this;
}

WrongCat::~WrongCat() {std::cout << RED << "WrongCat destructor called\n" << RESET;}

void WrongCat::makeSound() const {
	std::cout << RED << "WrongMiaou\n" << RESET;
}