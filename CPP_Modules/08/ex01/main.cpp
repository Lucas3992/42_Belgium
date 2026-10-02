#include "Span.hpp"

int main() {
	std::srand(time(NULL));

	try {
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
		std::cout << std::string(70, '-') << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		Span s = Span(110);
		std::set<int> set;
		size_t spanSize = s.getSize();
		while (set.size() < spanSize)
			set.insert((rand() % 2000001) - 1000000);
		s.addNumber(set.begin(), set.end());
		s.printMin();
		s.printMax();
		std::cout << s.shortestSpan() << std::endl;
		std::cout << s.longestSpan() << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}