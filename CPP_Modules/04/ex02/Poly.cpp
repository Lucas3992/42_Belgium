#include "Poly.hpp"

AAnimal::AAnimal() {
	type = "AAnimal";
	std::cout << "AAnimal constructor called\n";
}

AAnimal::AAnimal(const AAnimal& other) : type(other.type) {
	std::cout << "AAnimal copy constructor called\n";
}

AAnimal& AAnimal::operator=(const AAnimal& other) {
	type = other.type;
	std::cout << "AAnimal copy assignment operator called\n";
	return *this;
}

AAnimal::~AAnimal() {std::cout << "AAnimal destructor called\n";}

std::string AAnimal::getType() const {
	return type;
}

Cat::Cat() : brain(new Brain()) {
	type = "Cat";
	std::cout << RED << "Cat constructor called\n" << RESET;
}

Cat::Cat(const Cat& other) : AAnimal (other), brain(new Brain(*other.brain)) {
	std::cout << RED << "Cat copy constructor called\n" << RESET;
}

Cat& Cat::operator=(const Cat& other) {
	if (this != &other) {
		AAnimal::operator=(other);
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

Dog::Dog(const Dog& other) : AAnimal (other), brain(new Brain(*other.brain)) {
	std::cout << YELLOW << "Dog copy constructor called\n" << RESET;
}

Dog& Dog::operator=(const Dog& other) {
	if (this != &other){
		AAnimal::operator=(other);
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
