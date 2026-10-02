#include <iostream>
#include "Array.hpp"

#define MAX_VAL 750
int main(int, char**) {
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++) {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++) {
        if (mirror[i] != numbers[i]) {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try {
        numbers[-2] = 0;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    try {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
        numbers[i] = rand();
    delete [] mirror;

	Array<char> charArray(10);

	for (unsigned int i = 0; i < charArray.size(); ++i)
        charArray[i] = 'a' + std::rand() % 26;

    std::cout << "charArray: ";
    for (unsigned int i = 0; i < charArray.size(); ++i)
        std::cout << charArray[i] << ' ';
    std::cout << "\n";
	
    try {
        charArray[10] = 'X';
    } 
	catch (const std::exception& e) {
        std::cout << "caught exception (10): " << e.what() << "\n";
    }

    try {
        charArray[-1] = 'Y';
    } 
	catch (const std::exception& e) {
        std::cout << "caught exception (-1): " << e.what() << "\n";
    }

    return 0;
}