#include "Fixed.hpp"

Fixed::Fixed() : value(0) {
    //std::cout << "Default constructor called\n";
}

//equivalent a 2^fract donc 2^8 donc 256;
Fixed::Fixed(const int n) : value(n * (1 << fract)) {
    //std::cout << "Int constructor called\n";
}

Fixed::Fixed(const float fl) : value(roundf(fl * (1 << fract))) {
    //std::cout << "Float constructor called\n";
}

Fixed::Fixed(const Fixed& src) {
	//std::cout << "Copy constructor called\n";
	this->operator=(src);
}

Fixed& Fixed::operator=(const Fixed& src) {
    //std::cout << "Copy assignment operator called\n";
	value = src.getRawBits();
    return *this;
}

Fixed::~Fixed() {
	//std::cout << "Destructor called\n";
}

int Fixed::getRawBits() const {
    //std::cout << "getRawBits member function called\n";
    return value;
}

void Fixed::setRawBits(int const raw) {
	value = raw;
}

int Fixed::toInt() const {
    int	integer = value >> fract;
	return integer;
}

float Fixed::toFloat() const {
	float fl = value / (float)(1 << fract);
	return fl;
}

std::ostream& operator<<(std::ostream& stream, const Fixed& f) {
	stream << f.toFloat();
	return stream;
}

bool Fixed::operator>(Fixed const &other) const {
	if (value > other.value)
		return true;
	return false;
}

bool Fixed::operator<(Fixed const &other) const {
	if (value < other.value)
		return true;
	return false;
}

bool Fixed::operator>=(Fixed const &other) const {
	if (value > other.value || value == other.value)
		return true;
	return false;
}

bool Fixed::operator<=(Fixed const &other) const {
	if (value < other.value || value == other.value)
		return true;
	return false;
}

bool Fixed::operator==(Fixed const &other) const {
	if (value == other.value)
		return true;
	return false;
}

bool Fixed::operator!=(Fixed const &other) const {
	if (value != other.value)
		return true;
	return false;
}

Fixed Fixed::operator-(Fixed const &other) const {
	Fixed	result;

	result.setRawBits(getRawBits() - other.getRawBits());
	return result;
}

Fixed Fixed::operator+(Fixed const &other) const {
	Fixed	result;

	result.setRawBits(getRawBits() + other.getRawBits());
	return result;
}

Fixed Fixed::operator*(Fixed const &other) const {
	Fixed		result;
	long long	tmp;

	tmp = (long long)getRawBits() * other.getRawBits();
	result.setRawBits(tmp >> fract);
	return result;
}

Fixed Fixed::operator/(Fixed const &other) const {
	Fixed	result;
	long long	tmp;

	tmp = (long long)getRawBits() << fract;
	result.setRawBits(tmp / other.getRawBits());
	return result;
}

Fixed &Fixed::operator++() {
	setRawBits(getRawBits() +1);
	return *this;//return lobjet modifie
}

//par convention, mettre int comme parametre bidon pour pas confondre les deux fct;
Fixed Fixed::operator++(int) {
	Fixed	tmp;

	tmp = *this;
	setRawBits(getRawBits() +1);
	return tmp;//return lancien objet 
}

Fixed &Fixed::operator--() {
	setRawBits(getRawBits() -1);
	return *this;
}

Fixed Fixed::operator--(int) {
	Fixed	tmp;

	tmp = *this;
	setRawBits(getRawBits() -1);
	return tmp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) {
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}

Fixed const& Fixed::min(Fixed const &a, Fixed const &b) {
	if (a.getRawBits() < b.getRawBits())
		return a;
	return b;
}

Fixed& Fixed::max(Fixed &a, Fixed &b) {
	if (a.getRawBits() > b.getRawBits())
		return a;
	return b;
}

Fixed const& Fixed::max(Fixed const &a, Fixed const &b) {
	if (a.getRawBits() > b.getRawBits())
		return a;
	return b;
}
