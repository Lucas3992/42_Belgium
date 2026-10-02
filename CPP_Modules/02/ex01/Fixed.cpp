#include "Fixed.hpp"

Fixed::Fixed() : value(0) {
    std::cout << "Default constructor called\n";
}

//equivalent a 2^fract donc 2^8 donc 256;
Fixed::Fixed(const int n) : value(n * (1 << fract)) {
    std::cout << "Int constructor called\n";
}

Fixed::Fixed(const float fl) : value(roundf(fl * (1 << fract))) {
    std::cout << "Float constructor called\n";
}

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

//ici cest dans lautre sens, on decale les bits pour faire /256;
int Fixed::toInt() const {
    int	integer = value >> fract;
	return integer;
}

float Fixed::toFloat() const {
	float	fl = value / (float)(1 << fract);
	return fl;
}

std::ostream& operator<<(std::ostream& stream, const Fixed& f) {
	stream << f.toFloat();
	return stream;
}
