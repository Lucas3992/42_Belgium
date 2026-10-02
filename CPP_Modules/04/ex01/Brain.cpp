#include "Brain.hpp"

Brain::Brain() {
	std::cout << GREEN << "Brain constructor called\n" << RESET;
}

Brain::Brain(const Brain& other) {
	for (int i = 0; i < 100; i++)
            ideas[i] = other.ideas[i];
	std::cout << GREEN << "Brain copy constructor called\n" << RESET;
}

Brain& Brain::operator=(const Brain& other) {
    if (this != &other)
    {
        for (int i = 0; i < 100; i++)
            ideas[i] = other.ideas[i];
    }
	std::cout << GREEN << "Brain copy assignment operator called\n" << RESET;
	return *this;
}

Brain::~Brain() {std::cout << GREEN << "Brain destructor called\n" << RESET;}
