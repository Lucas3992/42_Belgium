#ifndef INTERN_HPP
# define INTERN_HPP

# include "AForm.hpp"
# include "ShrubberyCreationForm.hpp"
# include "PresidentialPardonForm.hpp"
# include "RobotomyRequestForm.hpp"

class Intern {
    public :
    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);
    ~Intern();

    AForm* makeForm(const std::string& formName, const std::string& target);
    AForm* newShrub(const std::string& target);
    AForm* newPres(const std::string& target);
    AForm* newRobo(const std::string& target);

    class InvalidFormNameException : public std::exception {
        public:
            virtual const char *what() const throw();
    };
};

#endif