#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(const Intern& other) {
    (void)other;
}

Intern& Intern::operator=(const Intern& other) {
    (void)other;
    return *this;
}

Intern::~Intern() {};

AForm* Intern::newShrub(const std::string& target) {
    return new ShrubberyCreationForm(target);
}

AForm* Intern::newPres(const std::string& target) {
    return new PresidentialPardonForm(target);
}

AForm* Intern::newRobo(const std::string& target) {
    return new RobotomyRequestForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    std::string names[3] = {"presidential pardon", "robotomy request", "shrubbery creation"};
    AForm* (Intern::*fct[3])(const std::string&) = {&Intern::newPres, &Intern::newRobo, &Intern::newShrub};

    for (int i = 0; i < 3; i++) {
        if (names[i] == formName) {
            std::cout << "Intern creates " << names[i] << " form\n";
            return (this->*fct[i])(target);
        }
    }
    throw Intern::InvalidFormNameException();
}

const char* Intern::InvalidFormNameException::what() const throw() {
		return "Invalid form! Damn intern!";
}
