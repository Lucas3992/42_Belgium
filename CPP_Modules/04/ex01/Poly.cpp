#include "Poly.hpp"

Animal::Animal() {
	type = "Animal";
	std::cout << "Animal constructor called\n";
}

Animal::Animal(const Animal& other) : type(other.type) {
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

Cat::Cat() : brain(new Brain()) {
	type = "Cat";
	std::cout << RED << "Cat constructor called\n" << RESET;
}

Cat::Cat(const Cat& other) : Animal (other), brain(new Brain(*other.brain)) {
	std::cout << RED << "Cat copy constructor called\n" << RESET;
}

Cat& Cat::operator=(const Cat& other) {
	if (this != &other) {
		Animal::operator=(other);
		delete brain;
		brain = new Brain(*other.brain);
	}
	std::cout << RED << "Cat copy assignment operator called\n" << RESET;
	return *this;
}

Cat::~Cat() {
	std::cout << RED << "Cat destructor called\n" << RESET;
	delete brain;
}

void Cat::makeSound() const {
	std::cout << RED << "miaou\n" << RESET;
}

Dog::Dog() : brain(new Brain()) {
	type = "Dog";
	std::cout << YELLOW << "Dog constructor called\n" << RESET;
}

Dog::Dog(const Dog& other) : Animal (other), brain(new Brain(*other.brain)) {
	std::cout << YELLOW << "Dog copy constructor called\n" << RESET;
}

Dog& Dog::operator=(const Dog& other) {
	if (this != &other){
		Animal::operator=(other);
		delete brain;
		brain = new Brain(*other.brain);
	}
	std::cout << YELLOW << "Dog copy assignment operator called\n" << RESET;
	return *this;
}

Dog::~Dog() {
	std::cout << YELLOW << "Dog destructor called\n" << RESET;
	delete brain;
}

void Dog::makeSound() const {
	std::cout << YELLOW << "waf waf\n" << RESET;
}
