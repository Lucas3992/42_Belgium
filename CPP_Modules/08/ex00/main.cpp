#include "easyfind.hpp"

int main() {
	std::srand(time(NULL));

	size_t size = 0 + (rand() % 10);
	std::vector<int> v;

	std::cout << "Size: " << size << std::endl;
	std::cout << "Digits: ";
	if (size > 0) {
		for (size_t i = 0; i < size; i++) {
			v.push_back(0 + (rand() % 10));
			std::cout << v.at(i) << " ";
		}
	}
	std::cout << std::endl;
	try {
		std::vector<int>::iterator found = easyfind(v, 1);
		size_t index = found - v.begin();
		std::cout << "Found " << *found << " at " << index << std::endl;
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}