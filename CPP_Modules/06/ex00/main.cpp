#include "ScalarConverter.hpp"

int main(int ac, char** av) {
    if (ac != 2) {
        std::cout << "Wrong input: usage: ./ex00 <ArgsToConvert>\n";
        return 1;
    }
    std::string input = av[1];
    ScalarConverter::convert(input);

    /* //tests:
    (void)ac; (void)av;
    std::string tests[] = {
        "a", "Z", "!", " ", //->char
        "0", "42", "-42", "+123",//->int
        "2147483647", "-2147483648",
        "0.0f", "42.0f", "-4.2f", "+3333333.14f",//->float
        "42.f", ".42f", "0.42f",
        "0.0", "42.0", "-4.2", "+44444.14",//->double
        "42.", ".42", "0.42",
        "nan", "+inf", "-inf",//->pseudo lit
        "nanf", "+inff", "-inff",
        "abc", "99.9*", "4.2ff", "++1", "--1",
        "4..2", "1.2.3", "", "   ", "f42", "9999999999999999999999999.99f",
        "-222222222222222222222222222222222.22222222222222222222222", ""
    };
    
    for (int i = 0; i < 43; i++) {
        std::cout << "TEST " << i+1 << ": \"" << tests[i] << "\"" << std::endl;
        ScalarConverter::convert(tests[i]);
        std::cout << std::string(70, '-') << std::endl;
    } */

    return 0;
}