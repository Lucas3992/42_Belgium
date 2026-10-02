#include "RPN.hpp"
//regle : il faut (chiffre -1) doperateurs && 
//au moment ou il lit loperator, doit y avoir au moins 2 int dans la stack
int main(int ac, char** av) {
    if (ac != 2) {
        std::cerr << "Error: usage: ./RPN \"digits and operations\"\n";
        return 1;
    }
    try {
        RPN rpn;
        rpn.evaluate(av[1]);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
