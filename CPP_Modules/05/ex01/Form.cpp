#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() {
    name = "unknown";
    isSigned = false;
    gradeToSign = 150;
    gradeToExecute = 150;
}

Form::Form(std::string newName, int ToSign, int ToExecute) {
    name = newName;
    isSigned = false;
    gradeToSign = ToSign;
    gradeToExecute = ToExecute;
}

Form::Form(const Form& other) {
    name = other.name;
    isSigned = other.isSigned;
    gradeToSign = other.gradeToSign;
    gradeToExecute = other.gradeToExecute;
}

Form& Form::operator=(const Form& other) {
    if (this != &other) {
        name = other.name;
        isSigned = other.isSigned;
        gradeToSign = other.gradeToSign;
        gradeToExecute = other.gradeToExecute;
    }
    return *this;
}

Form::~Form() {}

std::string Form::getName() const {
    return name;
}

bool Form::getIsSigned() const {
    return isSigned;
}

int Form::getGradeToSign() const {
    return gradeToSign;
}

int Form::getGradeToExecute() const {
    return gradeToExecute;
}

void Form::beSigned(Bureaucrat& b) {
    if (b.getGrade() <= getGradeToSign()) {
        isSigned = true;
        std::cout << b << " signed " << *this << std::endl;
    }
    else {
        std::cout << b << " couldn't sign " << *this << " because ";
        throw GradeTooLowException();
    }
}

const char* Form::GradeTooHighException::what() const throw() {
		return "Grade is too damn high!\n";
}

const char* Form::GradeTooLowException::what() const throw() {
		return "Grade is too damn low!\n";
}

std::ostream& operator<<(std::ostream& output, Form& f) {
    output << "Form: " << f.getName() << ", " << f.getIsSigned() << ", " 
    << f.getGradeToSign() << ", " << f.getGradeToExecute();
    return output;
}