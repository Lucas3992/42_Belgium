#include "BitcoinExchange.hpp"

int main(int ac, char** av) {
    if (ac != 2) {
        std::cerr << "Error: usage ./btc input.txt\n";
        return 1;
    }
    try {
        btc btc;
        btc.loadDatabase("data.csv");
        btc.processInput(av[1]);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
