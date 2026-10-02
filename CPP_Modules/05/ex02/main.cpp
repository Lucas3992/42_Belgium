#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main() {
    std::srand(std::time(NULL));

    try {
        Bureaucrat boss("BigBozze", 1);
        ShrubberyCreationForm shrub("home");

        boss.signForm(shrub);
        boss.executeForm(shrub);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "---------------------------------------------------------\n";
    try {
        Bureaucrat boss("BigBozze", 1);
        ShrubberyCreationForm shrub("garden");

        boss.executeForm(shrub);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "---------------------------------------------------------\n";
    try {
        Bureaucrat low("Intern", 150);
        ShrubberyCreationForm shrub("park");

        low.signForm(shrub);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "---------------------------------------------------------\n";
    try {
        Bureaucrat signer("Signer", 100);
        Bureaucrat executor("Executor", 140);
        ShrubberyCreationForm shrub("yard");

        signer.signForm(shrub);
        executor.executeForm(shrub);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "---------------------------------------------------------\n";
    try {
        Bureaucrat boss("BigBozze", 1);
        RobotomyRequestForm robo("Bender");

        boss.signForm(robo);
        boss.executeForm(robo);
        boss.executeForm(robo);
        boss.executeForm(robo);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "---------------------------------------------------------\n";
    try {
        Bureaucrat president("President", 1);
        PresidentialPardonForm pardon("Fry");

        president.signForm(pardon);
        president.executeForm(pardon);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}