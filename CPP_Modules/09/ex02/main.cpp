#include "PmergeMe.hpp"
//`shuf -i 1-100000 -n 3000 | tr "\n" " "`
int main(int ac, char** av) {
    if (ac < 2) {
        std::cerr << "Error: usage: ./PmergeMe numbers\n";
        return 1;
    }
    try {
        Sort s;
        for (int i = 1; i < ac; ++i)
            s.validateNb(av[i]);
        s.printBefore();
        s.sort();
        s.printAfter();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
