#include "iter.hpp"

void printRandomNumber(int& random) {
    random = std::rand() % 100;
    std::cout << random << " ";
}

void printRandomChar(char& c) {
    if (std::rand() % 2 == 0) {
        c = 'a' + std::rand() % 26;
        std::cout << c;
    }
    else {
        c = 'A' + std::rand() % 26;
        std::cout << c;
    }
}

void replaceByEmoji(const std::string& str) {
    if (str == "Rock")
        std::cout << "🪨" << "  ";
    else if (str == "Paper")
        std::cout << "🧻" << " ";
    else if (str == "Scissors")
    std::cout << "✂️" << std::endl;
}

void printConst(const int& n) {
    std::cout << n << " ";
}

int main() {
    std::srand(std::time(NULL));

    size_t size = std::rand() % 10;
    std::cout << "Size: " << size << std::endl;
    int* intArray = new int[size];
    iter(intArray, size, printRandomNumber);
    std::cout << std::endl << std::string(70, '-') << std::endl;
	delete[] intArray;

    size = std::rand() % 7;
    std::cout << "Size: " << size << std::endl;
    char* charArray = new char[size];
    iter(charArray, size, printRandomChar);
    std::cout << std::endl << std::string(70, '-') << std::endl;
	delete[] charArray;

    const std::string stringArray[3] = {"Rock", "Paper", "Scissors"};
    iter(stringArray, 3, replaceByEmoji);
    std::cout << std::string(70, '-') << std::endl;

    return 0;
}