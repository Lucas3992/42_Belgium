#include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN &o) : _stack(o._stack) {}
RPN& RPN::operator=(const RPN &o) {
    if (this != &o)
        _stack = o._stack;
    return *this;
}
RPN::~RPN() {}
RPN::RPNException::RPNException(const std::string msg) : _msg("Error: " + msg) {}
RPN::RPNException::~RPNException() throw() {}
const char* RPN::RPNException::what() const throw() {return _msg.c_str();}

bool RPN::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

long RPN::apply(long a, long b, char op) {
    if (op == '/' && b == 0)
        throw RPNException("cannot divide by 0");
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
        return a / b;
    throw RPNException("unknown operator");
}

void RPN::doublePushAndPop(const char op) {
    long b = _stack.top();
    _stack.pop();
    long a = _stack.top();
    _stack.pop();
    _stack.push(apply(a, b, op));
}

void RPN::evaluate(const std::string& argv) {
    std::istringstream iss(argv);
    std::string token;
    while (iss >> token) {//iss skip les espace et met le char lu dans token
        if (token.size() == 1 && isdigit(token[0]))
            _stack.push(token[0] - '0');
        else if (token.size() == 1 && isOperator(token[0])) {
            if (_stack.size() < 2)
				throw RPNException("not enough operands");
            doublePushAndPop(token[0]);
        }
        else
            throw RPNException("unknown token");
    }
	if (_stack.size() == 1)
		std::cout << _stack.top() << std::endl;
	else
		throw RPNException("wrong input");
}