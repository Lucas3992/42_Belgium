#include "Poly.hpp"

Animal::Animal() {
	type = "Animal";
	std::cout << "Animal constructor called\n";
}

Animal::Animal(const Animal& other) {
	operator=(other);
	std::cout << "Animal copy constructor called\n";
}

Animal& Animal::operator=(const Animal& other) {
	type = other.type;
	std::cout << "Animal copy assignment operator called\n";
	return *this;
}

Animal::~Animal() {std::cout << "Animal destructor called\n";}

std::string Animal::getType() const {
	return type;
}

void Animal::makeSound() const {
    std::cout << "*animal sound*\n";
}

Cat::Cat() {
	type = "Cat";
	std::cout << "Cat constructor called\n";
}

Cat::Cat(const Cat& other) : Animal (other) {
	std::cout << "Cat copy constructor called\n";
}

Cat& Cat::operator=(const Cat& other) {
	(void)other;//finir ici
	std::cout << "Cat copy assignment operator called\n";
	return *this;
}

Cat::~Cat() {std::cout << "Cat destructor called\n";}

void Cat::makeSound() const {
	std::cout << "miaou\n";
}

Dog::Dog() {
	type = "Dog";
	std::cout << "Dog constructor called\n";
}

Dog::Dog(const Dog& other) : Animal (other) {
	std::cout << "Dog copy constructor called\n";
}

Dog& Dog::operator=(const Dog& other) {
	(void)other;//pareil finir ici
	std::cout << "Dog copy assignment operator called\n";
	return *this;
}

Dog::~Dog() {std::cout << "Dog destructor called\n";}

void Dog::makeSound() const {
	std::cout << "waf waf\n";
}
