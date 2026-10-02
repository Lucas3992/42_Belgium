#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>

class RPN {
    private:
        std::stack<long> _stack;

        bool    isOperator(char c) const;
        long    apply(long a, long b, char op);
    public:
        RPN();
        RPN(const RPN& o);
        RPN& operator=(const RPN& o);
        ~RPN();

        void    doublePushAndPop(const char op);
        void    evaluate(const std::string& argv);

    class RPNException : public std::exception {
        private:
            std::string _msg;
        public:
            RPNException(const std::string msg);
            virtual ~RPNException() throw();
            virtual const char* what() const throw ();
    };
};

#endif