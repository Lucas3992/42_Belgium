#include "Bureaucrat.hpp"

int main() {
	try {
		Bureaucrat d("Dede la deconne", 150);
		std::cout << "Creating " << d;
		d.decrementGrade();
	}
	catch (const std::exception& e) {std::cerr << e.what();}

	try {
		Bureaucrat g("Gege le bigbozze", 1);
		std::cout << "Creating " << g;
		g.incrementGrade();
	}
	catch (const std::exception& e) {std::cerr << e.what();}

	try {
        std::cout << "Trying to create Jean-High but ";
		Bureaucrat j("Jean-high", 0);
	}
	catch (const std::exception& e) {std::cerr << e.what();}

	try {
		Bureaucrat l("Jean-low", 151);
		std::cout << "Trying to create Jean-Low but ";
	}
	catch (const std::exception& e) {std::cerr << e.what();}

	return 0;
}