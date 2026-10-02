#include "Fixed.hpp"

Fixed::Fixed() : value(0) {std::cout << "Default constructor called\n";}

Fixed::Fixed(const Fixed& src) {
	
	std::cout << "Copy constructor called\n";
	this->operator=(src);
}

Fixed& Fixed::operator=(const Fixed& src) {
    
    std::cout << "Copy assignment operator called\n";
	value = src.getRawBits();
    return *this;
}

Fixed::~Fixed() {std::cout << "Destructor called\n";}

int Fixed::getRawBits() const {

    std::cout << "getRawBits member function called\n";
    return value;
}

void Fixed::setRawBits(int const raw) {

	value = raw;
}
