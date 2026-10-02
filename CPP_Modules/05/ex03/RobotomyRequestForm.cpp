#include "RobotomyRequestForm.hpp"
#include "Bureaucrat.hpp"

RobotomyRequestForm::RobotomyRequestForm()
: AForm("RobotomyRequestForm", 72, 45) {
    _target = "unknown";
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
: AForm("RobotomyRequestForm", 72, 45) {
    _target = target;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
: AForm("RobotomyRequestForm", 72, 45) {
    _target = other._target;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
    if (this != &other)
        _target = other._target;
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {} 

void RobotomyRequestForm::executeAction() const {
    std::cout << "Drilling noises... ";
    if (std::rand() % 2 == 0)
        std::cout << _target << " has been successfully robotomized\n";
    else
        std::cout << "Robotomy failed\n";
}