#include "Base.hpp"

int main() {
    std::srand(std::time(NULL));

    Base* test1 = generate();
    std::cout << "PTR identify: ";
    identify(test1);
    std::cout << "REF identify: ";
    identify(*test1);
    
    delete test1;
    return 0;
}