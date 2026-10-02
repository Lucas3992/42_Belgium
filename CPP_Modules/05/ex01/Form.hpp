#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>

class Bureaucrat;

class Form {
    private:
        std::string name;
        bool isSigned;
        int gradeToSign;
        int gradeToExecute;
    public:
        Form();
        Form(std::string newName, int ToSign, int ToExecute);
        Form(const Form& other);
        Form& operator=(const Form& other);
        ~Form();

		std::string getName() const ;
		bool getIsSigned() const ;
		int getGradeToSign() const ;
		int getGradeToExecute() const ;

		void beSigned(Bureaucrat& b);

        class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

std::ostream& operator<<(std::ostream& output, Form& f);

#endif