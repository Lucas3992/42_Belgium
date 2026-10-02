#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"

int main()
{
    std::srand(std::time(NULL));

    Intern someRandomIntern;
    Bureaucrat boss("BigBozze", 1);
    Bureaucrat peon("Peon", 150);
    AForm *form1 = NULL;
    AForm *form2 = NULL;
    AForm *form3 = NULL;

    try {
        form1 = someRandomIntern.makeForm("robotomy request", "Bender");
        std::cout << *form1 << std::endl;
        peon.signForm(*form1);//devrait echouer
        boss.signForm(*form1);//devrait marcher
        peon.executeForm(*form1);//devrait echouer
        boss.executeForm(*form1);//devrait marcher
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "---------------------------------------------------------\n";

    try {
        form2 = someRandomIntern.makeForm("shrubbery creation", "Garden");
        std::cout << *form2 << std::endl;
        peon.signForm(*form2);//devrait echouer
        boss.signForm(*form2);//devrait marcher
        peon.executeForm(*form2);//devrait echouer
        boss.executeForm(*form2);//devrait marcher
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "---------------------------------------------------------\n";

    try {
        form3 = someRandomIntern.makeForm("fake request", "fake target");
        std::cout << *form3 << std::endl;
        boss.signForm(*form3);
        boss.executeForm(*form3);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
	delete form1;
	delete form2;
	delete form3;

	return 0;
}