#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

ShrubberyCreationForm::ShrubberyCreationForm()
: AForm("ShrubberyCreationForm", 145, 137) {
        _target = "unknown";
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
: AForm("ShrubberyCreationForm", 145, 137) {
        _target = target;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
: AForm("ShrubberyCreationForm", 145, 137) {
        _target = other._target;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
    if (this != &other) 
        _target = other._target;
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::executeAction() const {
    std::ofstream ofs((_target + "_shrubbery").c_str());
    if (!ofs)
        throw std::runtime_error("Failed to open shrubbery file");
    ofs << "   ccee88oo\n";
    ofs << " C8O8O8Q8PoOb o8oo\n";
    ofs << "dOB69QO8PdUOpugoO9bD\n";
    ofs << "CgggbU8OU qOp qOdoUOdcb\n";
    ofs << "    6OuU  /p u gcoUodpP\n";
    ofs << "      \\\\//  /douUP\n";
    ofs << "        \\\\////\n";
    ofs << "         |||\n";
    ofs << "         |||\n";
    ofs << "         |||\n";
    ofs << "   .....//||||....\n";
    ofs.close();
}