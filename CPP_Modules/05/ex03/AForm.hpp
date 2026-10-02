#ifndef AForm_HPP
# define AForm_HPP

# include <iostream>

class Bureaucrat;

class AForm {
    private:
        std::string name;
        bool isSigned;
        int gradeToSign;
        int gradeToExecute;
    public:
        AForm();
        AForm(std::string newName, int ToSign, int ToExecute);
        AForm(const AForm& other);
        AForm& operator=(const AForm& other);
        virtual ~AForm();

		std::string getName() const ;
		bool getIsSigned() const ;
		int getGradeToSign() const ;
		int getGradeToExecute() const ;

		void beSigned(Bureaucrat& b);
        virtual void execute(Bureaucrat const& executor) const;

        class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
        class FormNotSignedException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
    protected:
        virtual void executeAction() const = 0;
};

std::ostream& operator<<(std::ostream& output, AForm& f);

#endif