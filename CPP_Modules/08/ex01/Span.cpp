#include "Span.hpp"

Span::Span() {}

Span::Span(unsigned int n) : v(), _size(n){}

Span::Span(const Span& other) : v(other.v), _size(other._size) {}

Span& Span::operator=(const Span& other) {
	if (this != &other) {
		v = (other.v);
		_size = other._size;
	}
	return *this;
}

Span::~Span() {}

const char* Span::FullException::what() const throw() {
	return "Vector full";
}

void Span::addNumber(int toAdd) {
	if (v.size() < _size)
		v.push_back(toAdd);
	else
		throw FullException();
}

unsigned int Span::shortestSpan() const {
    if (v.size() <= 1)
        return 0;
    std::vector<int> sorted(v);
    std::sort(sorted.begin(), sorted.end());
    unsigned int sDiff = std::numeric_limits<unsigned int>::max();
    for (size_t i = 0; i < sorted.size() -1; i++) {
        unsigned int diff = (unsigned int)(sorted[i + 1] - sorted[i]);
        if (diff < sDiff)
            sDiff = diff;
    }
    return sDiff;
}

unsigned int Span::longestSpan() const {
	if (v.size() <= 1)
		return 0;
	unsigned int max = *std::max_element(v.begin(), v.end());
	unsigned int min = *std::min_element(v.begin(), v.end());

	return (max - min);
}

size_t Span::getSize() const {
	return _size;
}

void Span::printMin() const {
	if (v.empty()) {
		std::cout << "Empty vector\n";
		return;
	}
	std::vector<int> sorted(v);
	std::sort(sorted.begin(), sorted.end());
	int min = sorted[0];
	std::cout << "Min: "  << min << std::endl;
}

void Span::printMax() const {
	if (v.empty()) {
		std::cout << "Empty vector\n";
		return;
	}
	int max = *std::max_element(v.begin(), v.end());
	std::cout << "Max: " << max << std::endl;
}