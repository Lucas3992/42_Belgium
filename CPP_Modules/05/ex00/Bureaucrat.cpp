#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() {
	_name = "unknown";
	_grade = 150;
}

Bureaucrat::Bureaucrat(const std::string name, int grade) {
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
	_name = name;
	_grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat& other) {
	_name = other._name;
	_grade = other._grade;
}

Bureaucrat& Bureaucrat::operator=(Bureaucrat& other) {
	if (this != &other) {
	_name = other._name;
	_grade = other._grade;
	}
	return *this;
}

Bureaucrat::~Bureaucrat() {}

std::string Bureaucrat::getName() {
	return _name;
}

int Bureaucrat::getGrade() const {
	return _grade;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
		return "Grade is too damn high!\n";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
		return "Grade is too damn low!\n";
}

void Bureaucrat::incrementGrade() {
	if (getGrade() -1 < 1) {
		std::cout << "Tried to upgrade " << _name << " but ";
		throw GradeTooHighException();
	}
	else
		_grade--;
}

void Bureaucrat::decrementGrade() {
	if (getGrade() +1 > 150) {
		std::cout << "Tried to downgrade " << _name << " but ";
		throw GradeTooLowException();
	}
	else
		_grade++;
}

std::ostream& operator<<(std::ostream& output, Bureaucrat& b) {
	output << b.getName() << ", bureaucrat grade " << b.getGrade() << std::endl;
	return output;
}