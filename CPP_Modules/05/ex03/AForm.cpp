#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() {
    name = "unknown";
    isSigned = false;
    gradeToSign = 150;
    gradeToExecute = 150;
}

AForm::AForm(std::string newName, int ToSign, int ToExecute) {
    name = newName;
    isSigned = false;
    gradeToSign = ToSign;
    gradeToExecute = ToExecute;
}

AForm::AForm(const AForm& other) {
    name = other.name;
    isSigned = other.isSigned;
    gradeToSign = other.gradeToSign;
    gradeToExecute = other.gradeToExecute;
}

AForm& AForm::operator=(const AForm& other) {
    if (this != &other) {
        name = other.name;
        isSigned = other.isSigned;
        gradeToSign = other.gradeToSign;
        gradeToExecute = other.gradeToExecute;
    }
    return *this;
}

AForm::~AForm() {}

std::string AForm::getName() const {
    return name;
}

bool AForm::getIsSigned() const {
    return isSigned;
}

int AForm::getGradeToSign() const {
    return gradeToSign;
}

int AForm::getGradeToExecute() const {
    return gradeToExecute;
}

void AForm::beSigned(Bureaucrat& b) {
    if (b.getGrade() <= getGradeToSign()) {
        isSigned = true;
        std::cout << b << " signed " << *this << std::endl;
    }
    else {
        std::cout << b << " couldn't sign " << *this << " because ";
        throw GradeTooLowException();
    }
}

const char* AForm::GradeTooHighException::what() const throw() {
	return "Grade is too damn high!\n";
}

const char* AForm::GradeTooLowException::what() const throw() {
	return "Grade is too damn low!\n";
}

const char* AForm::FormNotSignedException::what() const throw() {
    return "Form not signed!\n";
}

std::ostream& operator<<(std::ostream& output, AForm& f) {
    output << "AForm: " << f.getName() << ", " << f.getIsSigned() << ", " 
    << f.getGradeToSign() << ", " << f.getGradeToExecute();
    return output;
}

void AForm::execute(Bureaucrat const& executor) const {
    if (!getIsSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getGradeToExecute())
        throw GradeTooLowException();
    executeAction();
}
