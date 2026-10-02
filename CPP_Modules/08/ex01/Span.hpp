#ifndef SPAN_HPP
# define SPAN_HPP

# include <iostream>
# include <algorithm>
# include <vector>
# include <climits>
# include <limits>
# include <cstdlib>
# include <ctime>
# include <set>

class Span {
	private:
		std::vector<int> v;
		unsigned int _size;
	public:
		Span();
		Span(unsigned int n);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();

		size_t getSize() const;
		void printMin() const;
		void printMax() const;
		void addNumber(int toAdd);
		unsigned int shortestSpan() const;
		unsigned int longestSpan() const;

		template <typename it>
		void addNumber(it addMin, it addMax);

		class FullException : public std::exception {
			virtual const char* what() const throw();
		};
};

template <typename it>
void Span::addNumber(it addMin, it addMax) {
	if (v.size() < _size) {
		for (; addMin != addMax; addMin++)
			v.push_back(*addMin);
	}
	else
		throw Span::FullException();
}

#endif